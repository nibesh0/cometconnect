#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <portaudio.h>
#define SAMPLE_RATE 44100
#define FRAMES_PER_BUFFER 512
#define AUDIO_BUFFER (FRAMES_PER_BUFFER * sizeof(float))
#define PORT 8888
typedef struct {
    PaStream *stream;
    int connfd;
} audiod;
void error(const char *msg) {
    perror(msg);
    exit(1);
}

int audioCallbackS(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo *timeInfo, PaStreamCallbackFlags statusFlags, void *userData)
{
    audiod *audioData = (audiod *)userData;
    int connfd = audioData->connfd;
    const float *in = (const float *)inputBuffer;
    float *out = (float *)outputBuffer;
    char buffer[AUDIO_BUFFER];
    ssize_t bytes_sent = send(connfd, (const char *)in, AUDIO_BUFFER, 0);
    if (bytes_sent < 0)
    {
        error("Error sending data");
        return paAbort;
    }
    ssize_t bytes_received = recv(connfd, buffer, AUDIO_BUFFER, 0);
    if (bytes_received < 0)
    {
        error("Error receiving data");
        return paAbort;
    }
    else if (bytes_received == 0)
    {
        printf("Connection closed by the client\n");
        return paAbort;
    }
    memcpy(out, buffer, AUDIO_BUFFER);


    return paContinue;
    
}
int audioCallbackC(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo *timeInfo, PaStreamCallbackFlags statusFlags, void *userData)
{
    audiod *audioData = (audiod *)userData;
    int connfd = audioData->connfd;
    const float *in = (const float *)inputBuffer;
    float *out = (float *)outputBuffer;
    char buffer[AUDIO_BUFFER];
    ssize_t bytes_sent = send(connfd, (const char *)in, AUDIO_BUFFER, 0);
    if (bytes_sent < 0)
    {
        error("Error sending data");
        return paAbort;
    }
    ssize_t bytes_received = recv(connfd, buffer, AUDIO_BUFFER, 0);
    if (bytes_received < 0)
    {
        error("Error receiving data");
        return paAbort;
    }
    else if (bytes_received == 0)
    {
        printf("Connection closed by the client\n");
        return paAbort;
    }
    memcpy(out, buffer, AUDIO_BUFFER);


    return paContinue;
    
}
void *audio_Send(void *argc)
{
    int connfd = *(int *)argc;
    char buffer[AUDIO_BUFFER];
    printf("Client connected\n");

    PaError err = Pa_Initialize();
    if (err != paNoError)
    {
        error("PortAudio initialization failed");
    }

    PaStream *stream;
    audiod audioData;
    audioData.connfd = connfd;

    err = Pa_OpenDefaultStream(&stream, 1, 1, paFloat32, SAMPLE_RATE, FRAMES_PER_BUFFER, audioCallbackS, &audioData);
    if (err != paNoError)
    {
        error("PortAudio stream opening failed");
    }

    audioData.stream = stream;

    err = Pa_StartStream(stream);
    if (err != paNoError)
    {
        error("PortAudio stream start failed");
    }

    printf("Streaming audio...\n");

    printf("Press Enter to stop the server\n");
    while (1)
    {
    }
    
    getchar();

    err = Pa_StopStream(stream);
    if (err != paNoError)
    {
        error("PortAudio stream stop failed");
    }

    err = Pa_CloseStream(stream);
    if (err != paNoError)
    {
        error("PortAudio stream close failed");
    }

    Pa_Terminate();

    pthread_exit(NULL);
}

void *audio_Recv(void *argc){
    int sockfd = *(int *)argc;
    char buffer[AUDIO_BUFFER];
    PaError err = Pa_Initialize();
    if (err != paNoError) {
        error("initialization failed");
    }
    PaStream *stream;
    audiod audiod;
    audiod.connfd = sockfd;
    err = Pa_OpenDefaultStream(&stream, 1, 1, paFloat32, SAMPLE_RATE,FRAMES_PER_BUFFER, audioCallbackC, &audiod);
    audiod.stream = stream;
    Pa_StartStream(stream);
    printf("Streaming audio...\n");
    printf("Press Enter to stop the client\n");
    while (1)
    {
    }
    
    getchar();
    Pa_StopStream(stream);
    Pa_CloseStream(stream);
    Pa_Terminate();
    pthread_exit(NULL);
}