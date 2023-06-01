#include "messagef/message.h"
#include "filecon/fileshare.h"
#include "videof/videocall.h"
#include "scannerf/scanner.h"
#include "audiof/audio.h"
#include "logo/logo.h"
struct sockaddr_in servAudio;
socklen_t servlen2= sizeof(servAudio);
struct sockaddr_in serv;
socklen_t servlen = sizeof(serv);
int sockfd,audioSock;
int main(int argc,const char **argv)
{
if (argc < 2)
{
    printf("usage: <ip>");
    exit(1);
}
char ip[17];
strcpy(ip,argv[1]);

int port=6969;

while (1)
{
    // system("clear");
    printf("\033[0;31m");
    printf("%s",logo);
    printf("%s",logo2);
    printf("\033[0m");
    int choice;
    printf("Wellcome to cometconnect messaging Sservices\nChoose a option from bellow:-\n");
    printf("[1].Chatting(texting)\n");
    printf("[2].filesending\n");
    printf("[3].Videocall\n");
    printf("[4].Voicecall\n");
    printf("[9].For scan ip network\n");
    printf("[5].Quit\n");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        printf("chatting started...\n");
        if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
        perror("socket");
        exit(1);
        }
        serv.sin_family = AF_INET;
        serv.sin_addr.s_addr = inet_addr(ip);
        serv.sin_port = htons(port);
        memset(serv.sin_zero, 0, sizeof(serv.sin_zero));
        if (bind(sockfd, (struct sockaddr *)&serv, sizeof(serv)) < 0)
        {
        perror("bind");
        exit(1);
        }
        if (listen(sockfd, 2) < 0)
        {
            perror("listen");
            exit(1);
        }
        int newfd,newfd2;
        if ((newfd = accept(sockfd, (struct sockaddr *)&serv, &servlen)) < 0)
        {
        perror("accept");
        exit(1);
        }
        pthread_t messSend, messRec;
        pthread_create(&messSend, NULL, &send_messageServer, &newfd);
        pthread_create(&messRec, NULL, &recv_messageServer, &newfd);
        pthread_join(messSend, NULL);
        pthread_join(messRec, NULL);
        close(sockfd);
        close(newfd);
        break;
        case 2:
        printf("fileshare starting...\nChoose a option:\n");
        printf("[1]You want to sent the file\n");
        printf("[2]you wnat to recive the file\n");
        int fileChoice;
        scanf("%d", &fileChoice);
        switch (fileChoice)
        {
        case 1:
            send_file(ip, port);
            break;
        case 2:
            recive_file(ip, port);
            break;
        default:
            printf("\033[0;31m");
            printf("[-1]not a valid choice\n");
            printf("\033[0m");
            break;
        }

        break;
        case 3:




        printf("videocall\n");
        if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
        perror("socket");
            exit(1);
        }
        if ((audioSock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
        perror("socket3");
            exit(1);
        }
        serv.sin_family = AF_INET;
        serv.sin_addr.s_addr = inet_addr(argv[1]);
        serv.sin_port = htons(port);
        memset(serv.sin_zero, 0, sizeof(serv.sin_zero));
        servAudio.sin_family = AF_INET;
        servAudio.sin_addr.s_addr = inet_addr(argv[1]);
        servAudio.sin_port = htons(6970);
        memset(servAudio.sin_zero, 0, sizeof(serv.sin_zero));
        if (bind(sockfd, (struct sockaddr *)&serv, sizeof(serv)) < 0)
        {
        perror("bind");
        exit(1);
        }
        if (bind(audioSock, (struct sockaddr *)&servAudio, sizeof(servAudio)) < 0)
        {
        perror("bind2");
        exit(1);
        }
        if (listen(sockfd, 3) < 0)
        {
        perror("listen");
        exit(1);
        }
        printf("%d\n",sockfd);
        if (listen(audioSock, 3) < 0)
        {
        perror("listen2");
        exit(1);
        }
        printf("%d\n",audioSock);
        if ((newfd = accept(sockfd, (struct sockaddr *)&serv, &servlen)) < 0)
        {
        perror("accept");
        exit(1);
        }
        if ((newfd2 = accept(audioSock, (struct sockaddr *)&servAudio, &servlen2)) < 0)
        {
        perror("accept2");
        exit(1);
        }
            pthread_t videoSend, videoRec,audioSer;
            pthread_create(&videoSend, NULL, &send_video, &newfd);
            pthread_create(&videoRec,NULL,&receive_video,&newfd);
            pthread_create(&audioSer, NULL, &audioServer, &newfd2);


            pthread_join(videoSend, NULL);
            pthread_join(videoRec, NULL);
            pthread_join(audioSer,NULL);
            close(sockfd);
            close(newfd);
            break;
        case 4:
            printf("voicecall\n");
            sockfd = socket(AF_INET, SOCK_STREAM, 0);
            if (sockfd < 0) {
                error("Error opening socket");
            }

            memset(&serv, 0, sizeof(serv));
            serv.sin_family = AF_INET;
            serv.sin_addr.s_addr = inet_addr(ip);
            serv.sin_port = htons(port);

            if (bind(sockfd, (struct sockaddr *)&serv, sizeof(serv)) < 0) {
            error("Error binding socket");
            }

            if (listen(sockfd, 1) < 0) {
                error("Error listening");
                }

            printf("Waiting for incoming connections...\n");

            newfd = accept(sockfd, (struct sockaddr *)&serv, &servlen);
            printf(".......dfgh%d\n",newfd);
            pthread_t audioRecv;
            pthread_create(&audioRecv,NULL,&audioServer,&newfd);
            pthread_join(audioRecv,NULL);
            close(sockfd);
            close(newfd);



            break;
        case 9:
            printf("starting scanning \n");
            scanner();
            break;
        case 5:
            goto exiT;
        default:
            printf("\033[0;31m");
            printf("[-1]not a valid choice\n");
            printf("\033[0m");
            sleep(2);
            break;
        }
    }
exiT:

    return 0;
}
