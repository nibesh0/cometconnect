#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
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
        if (cv::waitKey(1) == 27) {
            break;
        }
    }

    pthread_exit(NULL);
}
