#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
<<<<<<< HEAD
#include <stdlib.h>
#define BUFFER_SIZE 1024
typedef struct argum
{
int *sock;
struct sockaddr_in *serv;
} argum;




void* send_video(void* argc) {
    cv::VideoCapture capture(0);
    cv::Mat frame;
    std::vector<uchar> buffvec;
    int sockfd = *((int *)argc);
    char buffer[BUFFER_SIZE];
    int leftbt;

    while (1) {
        capture.read(frame);
        cv::imencode(".jpg", frame, buffvec);
        int vecsz = buffvec.size();

        if (send(sockfd, &vecsz, sizeof(vecsz), 0) == -1) {
            perror("send1vc");
            break;
        }

        int tsizb = 0;
        while (tsizb < vecsz) {
            int bytelast = vecsz - tsizb;
            int part;
            if (BUFFER_SIZE < bytelast)
                part = BUFFER_SIZE;
            else
                part = bytelast;
            if ((leftbt = send(sockfd, buffvec.data() + tsizb, part, 0)) == -1) {
                perror("send2vc");
                break;
            }
            tsizb += leftbt;
        }

        if (cv::waitKey(1) == 27) {
            break;
        }
    }

    pthread_exit(NULL);
}




void* receive_video(void* argc) {
    cv::Mat frame;
    char buffer[BUFFER_SIZE];
    std::vector<uchar> buffvec;
    int sock = *((int *)argc);

    while (1) {
        int tsizeb = 0;

        if (recv(sock, &tsizeb, sizeof(tsizeb), 0) == -1) {
            perror("recvvc");
            break;
        }

        buffvec.resize(tsizeb);
        int leftbt = 0;

        while (leftbt < tsizeb) {
            int bytelast = tsizeb - leftbt;
            int part;
            if (BUFFER_SIZE < bytelast)
                part = BUFFER_SIZE;
            else
                part = bytelast;
            int received = recv(sock, buffvec.data() + leftbt, part, 0);
            if (received == -1) {
                perror("recv2vc");
                break;
            }
            leftbt += received;
        }

        frame = cv::imdecode(buffvec, cv::IMREAD_COLOR);
        if (frame.empty()) {
            perror("emptyframe");
            break;
        }
        cv::imshow("call", frame);
        cv::waitKey(1);
    }

=======
#include <opencv2/opencv.hpp>
#define BUFFER_SIZE 1024
typedef struct argum
{
    int *sock;
    struct sockaddr_in *serv;
} argum;

void *recive_video(void *argc)
{
    argum *args = (argum *)argc;
    struct sockaddr_in serv_addr = *(args->serv);
    int sockfd = *(args->sock);
    socklen_t serv_len = sizeof(serv_addr);
    char buffer[BUFFER_SIZE];
    cv::Mat frame;
    printf("here2");
    while (1)
    {
        printf("here1");
        int bytesReceived = 0;
        int bytesToReceive = sizeof(bytesReceived);
        int recvResult = recvfrom(sockfd, &bytesReceived, bytesToReceive, 0, (struct sockaddr *)&serv_addr, &serv_len);
        if (recvResult == -1)
        {
            perror("recvfrom");
            exit(1);
        }

        std::vector<uchar> frameBuffer(bytesReceived);
        int totalBytesReceived = 0;
        while (totalBytesReceived < bytesReceived)
        {
            int remainingBytes = bytesReceived - totalBytesReceived;
            int bytesToReceive = std::min(BUFFER_SIZE, remainingBytes);

            int recvResult = recvfrom(sockfd, frameBuffer.data() + totalBytesReceived, bytesToReceive, 0, (struct sockaddr *)&serv_addr, &serv_len);
            if (recvResult == -1)
            {
                perror("recvfrom");
                exit(1);
            }
            totalBytesReceived += recvResult;
        }
        frame = cv::imdecode(frameBuffer, cv::IMREAD_COLOR);

        if (frame.empty())
        {
            fprintf(stderr, "Failed to decode frame\n");
            continue;
        }
        printf("here");
        cv::imshow("Received Video", frame);
        cv::waitKey(1);
    }

    cv::destroyAllWindows();
    pthread_exit(NULL);
}

void *send_video(void *argc)
{
    argum *args = (argum *)argc;
    struct sockaddr_in serv_addr = *(args->serv);
    int sockfd = *(args->sock);
    socklen_t serv_len = sizeof(serv_addr);
    
    cv::VideoCapture capture(0);
    cv::Mat frame;
    char buffer[BUFFER_SIZE];
    ssize_t bytesSent;
    while (1)
    {
        capture.read(frame);

        std::vector<uchar> frameBuffer;
        cv::imencode(".jpg", frame, frameBuffer);

        size_t bytesToSend = frameBuffer.size();
        bytesSent = sendto(sockfd, &bytesToSend, sizeof(bytesToSend), 0, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
        if (bytesSent == -1)
        {
            perror("sendto");
            exit(1);
        }

        size_t totalBytesSent = 0;
        while (totalBytesSent < bytesToSend)
        {
            size_t remainingBytes = bytesToSend - totalBytesSent;
            size_t bytesChunk = std::min(BUFFER_SIZE, (int)remainingBytes);

            bytesSent = sendto(sockfd, frameBuffer.data() + totalBytesSent, bytesChunk, 0, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
            if (bytesSent == -1)
            {
                perror("sendto");
                exit(1);
            }

            totalBytesSent += bytesSent;
        }

        if (cv::waitKey(1) == 27)
            break;
    }

    cv::destroyAllWindows();
>>>>>>> origin/main
    pthread_exit(NULL);
}
