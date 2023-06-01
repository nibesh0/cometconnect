#include "messagef/message.h"
#include "filecon/fileshare.h"
#include "videof/videocall.h"
#include "scannerf/scanner.h"
#include "audiof/audio.h"
#include "logo/logo.h"
int sockfd,sockfd2,audioSock;
struct sockaddr_in serv,serv2;
socklen_t servlen = sizeof(serv);
int port = 6969;
int audioPort = 6970;
int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        printf("usage: <ip>");
        exit(1);
    }
    while (1)
    {
        
        printf("\033[0;31m");
        printf("%s",logo2);
        printf("%s",logo);
        printf("\033[0m");
        int choice;
        printf("Wellcome to cometconnet messaging services\nChoose a option from bellow:-\n");
        printf("[1].Chatting(texting)\n");
        printf("[2].filesending\n");
        printf("[3].Videocall\n");
        printf("[4].Voicecall\n");
        printf("[9].scan the ip address\n");
        printf("[5].Quit\n");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("chatting started...\n");
            sockfd = socket(AF_INET, SOCK_STREAM, 0);
            serv.sin_addr.s_addr = inet_addr(argv[1]);
            serv.sin_family = AF_INET;
            serv.sin_port = htons(port);
            memset(serv.sin_zero, 0, sizeof(serv.sin_zero));
            if (connect(sockfd, (struct sockaddr *)&serv, sizeof(serv)) < 0)
            {
                perror("connect");
                exit(EXIT_FAILURE);
            }
            pthread_t messSend, messRec;

            pthread_create(&messRec, NULL, &recv_messageClient, &sockfd);
            pthread_create(&messSend, NULL, &send_messageClient, &sockfd);

            pthread_join(messRec, NULL);
            pthread_join(messSend, NULL);
            close(sockfd);
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
                send_file(argv[1], port);
                break;
            case 2:
                recive_file(argv[1], port);
                break;
            default:
                printf("\033[0;31m");
                printf("[-1]not a valid choice\n");
                printf("\033[0m");
                break;
            }
            break;
        case 3:
            printf("videocall starting...\n");
            sockfd2 = socket(AF_INET, SOCK_STREAM, 0);
            audioSock = socket(AF_INET, SOCK_STREAM, 0);
            serv.sin_addr.s_addr = inet_addr(argv[1]);
            serv.sin_family = AF_INET;
            serv.sin_port = htons(port);
            memset(serv.sin_zero, 0, sizeof(serv.sin_zero));
            serv2.sin_addr.s_addr = inet_addr(argv[1]);
            serv2.sin_family = AF_INET;
            serv2.sin_port = htons(audioPort);
            memset(serv2.sin_zero, 0, sizeof(serv2.sin_zero));
            if (connect(sockfd2, (struct sockaddr *)&serv, sizeof(serv)) < 0)
            {
                perror("connect");
                exit(EXIT_FAILURE);
            }
            // printf("%d\n",sockfd2);
            // printf("%d\n",audioSock);
            if (connect(audioSock, (struct sockaddr *)&serv2, sizeof(serv2)) < 0)
            {
                perror("connect2");
                exit(EXIT_FAILURE);
            }
            printf("%d\n",audioSock);
            pthread_t videoSend, videoRec,audioSer;

            pthread_create(&videoRec, NULL, &receive_video, &sockfd2);
            pthread_create(&videoSend, NULL, &send_video, &sockfd2);
            pthread_create(&audioSer,NULL,&audioClient,&audioSock);


            pthread_join(videoRec, NULL);
            pthread_join(videoSend, NULL);
            pthread_join(audioSer,NULL);
            close(sockfd2);
            close(audioSock);
            break;
        case 4:
            printf("voicecall\n");
            
            sockfd = socket(AF_INET, SOCK_STREAM, 0);
            if (sockfd < 0) {
                error("Error in socket");
            }
            memset(&serv, 0, sizeof(serv));
            serv.sin_addr.s_addr = inet_addr(argv[1]);
            serv.sin_family = AF_INET;
            serv.sin_port = htons(port);
        
            if (connect(sockfd, (struct sockaddr *)&serv, sizeof(serv)) < 0) {
                error("Error in connecting  ");
            }

            printf("Connected to the server\n");
            pthread_t audioCl;
            
            pthread_create(&audioCl,NULL,&audioClient,&sockfd);
            
            pthread_join(audioCl,NULL);
            close(sockfd);






            break;
        case 9:
            printf("starting scanning \n");
            scanner();
            break;
        case 5:
            goto exiT;
        default:
        system("clear");
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
