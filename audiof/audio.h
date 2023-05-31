#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <portaudio.h>
#include <unistd.h>
#include <pthread.h>

#define SAMPLE_RATE 44100
#define FRAMES_PER_BUFFER 512
#define AUDIO_BUFFER (FRAMES_PER_BUFFER * sizeof(float))

typedef struct {
    PaStream *stream;
    int sockfd;
} audiod;

void error(const char *msg) {
    perror(msg);
    exit(1);
}

int audioCallbackC(const void *inputBuffer, void *outputBuffer,unsigned long framesPerBuffer,const PaStreamCallbackTimeInfo *timeInfo,PaStreamCallbackFlags statusFlags, void *userData) {
    audiod *userAudio = (audiod *)userData;
    int sockfd = userAudio->sockfd;
    const float *in = (const float *)inputBuffer;
    float *out = (float *)outputBuffer;
    char buffer[AUDIO_BUFFER];
    int bytes_sent = send(sockfd, (const char *)in, AUDIO_BUFFER, 0);
    if (bytes_sent < 0) {
        error(" sending data");
        return paAbort;
    }

    int bytes_received = recv(sockfd, buffer, AUDIO_BUFFER, 0);
    if (bytes_received < 0) {
        error(" receiving data");
        return paAbort;
    } else if (bytes_received == 0) {
        printf("Connection closed by the server\n");
        return paAbort;
    }
    memcpy(out, buffer, AUDIO_BUFFER);

    return paContinue;
}
int audioCallbackS(const void *inputBuffer, void *outputBuffer,unsigned long framesPerBuffer,const PaStreamCallbackTimeInfo *timeInfo,PaStreamCallbackFlags statusFlags, void *userData) {
    audiod *userAudio = (audiod *)userData;
    int sockfd = userAudio->sockfd;
    const float *in = (const float *)inputBuffer;
    float *out = (float *)outputBuffer;
    char buffer[AUDIO_BUFFER];
    

    int bytes_received = recv(sockfd, buffer, AUDIO_BUFFER, 0);
    if (bytes_received < 0) {
        error(" receiving data");
        return paAbort;
    } else if (bytes_received == 0) {
        printf("Connection closed by the server\n");
        return paAbort;
    }
    int bytes_sent = send(sockfd, (const char *)in, AUDIO_BUFFER, 0);
    if (bytes_sent < 0) {
        error(" sending data");
        return paAbort;
    }
    memcpy(out, buffer, AUDIO_BUFFER);

    return paContinue;
}

void *audioClient(void *argc) {
    int sockfd = *((int *)argc);
    PaError err = Pa_Initialize();
    if (err != paNoError) {
        error("PortAudio initialization failed");
    }

    PaStream *stream;
    audiod userAudio;
    userAudio.sockfd = sockfd;

    err = Pa_OpenDefaultStream(&stream, 1, 1, paFloat32, SAMPLE_RATE,FRAMES_PER_BUFFER, audioCallbackC, &userAudio);
    if (err != paNoError) {
        error("PortAudio stream opening failed");
    }

    userAudio.stream = stream;
    err = Pa_StartStream(stream);
    if (err != paNoError) {
        error("PortAudio stream start failed");
    }

    printf("Streaming audio...\n");
    while (1)
    {

    }
    

    err = Pa_StopStream(stream);
    if (err != paNoError) {
        error("PortAudio stream stop failed");
    }

    err = Pa_CloseStream(stream);
    if (err != paNoError) {
        error("PortAudio stream close failed");
    }

    Pa_Terminate();

    close(sockfd);  

    pthread_exit(NULL);
}

void *audioServer(void *argc) {
    int connfd = *((int *)argc);
    PaError err = Pa_Initialize();
    if (err != paNoError) {
        error("PortAudio initialization failed");
    }

    PaStream *stream;
    audiod userAudio;
    userAudio.sockfd = connfd;
    printf("%d",connfd);
    err = Pa_OpenDefaultStream(&stream, 1, 1, paFloat32, SAMPLE_RATE,FRAMES_PER_BUFFER, audioCallbackS, &userAudio);
    if (err != paNoError) {
        error("PortAudio stream opening failed");
    }

    userAudio.stream = stream;
    err = Pa_StartStream(stream);
    if (err != paNoError) {
        error("PortAudio stream start failed");
    }

    printf("Streaming audio...\n");
    while (1)
    {

    }

    err = Pa_StopStream(stream);
    if (err != paNoError) {
        error("PortAudio stream stop failed");
    }

    err = Pa_CloseStream(stream);
    if (err != paNoError) {
        error("PortAudio stream close failed");
    }

    Pa_Terminate();

    close(connfd);  

    pthread_exit(NULL);
}