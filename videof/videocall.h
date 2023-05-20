#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
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
    pthread_exit(NULL);
}
