#include "messagef/message.h"
#include "filecon/fileshare.h"
#include "videof/videocall.h"
#include "scannerf/scanner.h"
#include "audiof/audio.h"
#include "logo/logo.h"
// const char logo[]="s";
struct sockaddr_in serv;
socklen_t servlen = sizeof(serv);
int sockfd;
int main(int argc,const char **argv)
{
// printf("enter the ip and port number.");
char ip[17];
strcpy(ip,argv[1]);

int port=6969;

// scanf("%s %d",ip,&port); 
while (1)
{
    // system("clear");
    printf("\033[0;31m");
    printf("%s",logo);
    printf("\033[0m");
    int choice;
    printf("Wellcome to gandu messaging Sservices\nChoose a option from bellow:-\n");
    printf("[1].Chatting(texting)\n");
    printf("[2].filesending(Nudes not allowed)\n");
    printf("[3].Videocall(nudes not allowed)\n");
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
        serv.sin_port = htons(6969);
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
        int newfd;
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
            send_file(ip, 6969);
            break;
        case 2:
            recive_file(ip, 6969);
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
        serv.sin_family = AF_INET;
        serv.sin_addr.s_addr = inet_addr(argv[1]);
        serv.sin_port = htons(6969);
        memset(serv.sin_zero, 0, sizeof(serv.sin_zero));
        if (bind(sockfd, (struct sockaddr *)&serv, sizeof(serv)) < 0)
        {
        perror("bind");
        exit(1);
        }
        if (listen(sockfd, 3) < 0)
        {
        perror("listen");
        exit(1);
        }
        if ((newfd = accept(sockfd, (struct sockaddr *)&serv, &servlen)) < 0)
        {
        perror("accept");
        exit(1);
        }
            pthread_t videoSend, videoRec,audioVrecv,audioVsend;
            pthread_create(&videoSend, NULL, &send_video, &newfd);
            pthread_create(&audioVsend, NULL, &audio_Send, &newfd);
            pthread_create(&videoRec, NULL, &receive_video, &newfd);
            pthread_create(&audioVrecv, NULL, &audio_Recv, &newfd);
            pthread_join(videoSend, NULL);
            pthread_join(audioVsend,NULL);
            pthread_join(videoRec, NULL);
            pthread_join(audioVrecv,NULL);
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
            serv.sin_port = htons(6969);

            if (bind(sockfd, (struct sockaddr *)&serv, sizeof(serv)) < 0) {
            error("Error binding socket");
            }

            if (listen(sockfd, 1) < 0) {
                error("Error listening");
                }

            printf("Waiting for incoming connections...\n");

            newfd = accept(sockfd, (struct sockaddr *)&serv, &servlen);
            pthread_t audioRecv,audioSend;
            pthread_create(&audioRecv,NULL,&audio_Recv,&newfd);
            // pthread_create(&audioSend,NULL,&audio_Send,&newfd);
            pthread_join(audioRecv,NULL);
            // pthread_join(audioSend,NULL);
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

            while (getchar() != '\n')
            {
                // Wait for Enter key to be pressed
            }
            break;
        }
    }
exiT:

    return 0;
}
