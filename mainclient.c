#include "messagef/message.h"
#include "filecon/fileshare.h"
#include "videof/videocall.h"
#include "scannerf/scanner.h"
#include "audiof/audio.h"
const char *logo =
    "'   _______     _____     _______    _______    _______    _______     _____     __   _    __   _    _______    _______    _______    \n"
    "'   |          |     |    |  |  |    |______       |       |          |     |    | \\  |    | \\  |    |______    |             |       \n"
    "'   |_____     |_____|    |  |  |    |______       |       |_____     |_____|    |  \\_|    |  \\_|    |______    |_____        |       \n"
    "'                                                                                                                                     \n";
int sockfd,sockfd2;
struct sockaddr_in serv;
socklen_t servlen = sizeof(serv);
int main(int argc, char const *argv[])
{
    if (argc < 3)
    {
        printf("usage: <ip> <port>");
        exit(1);
    }

    while (1)
    {
        
        printf("\033[0;31m");
        printf("%s",logo);
        printf("\033[0m");
        int choice;
        printf("Wellcome to gandu messaging services\nChoose a option from bellow:-\n");
        printf("[1].Chatting(texting)\n");
        printf("[2].filesending(Nudes not allowed)\n");
        printf("[3].Videocall(nudes not allowed)\n");
        printf("[4].Voicecall\n");
        printf("[5].Quit\n");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("chatting started...\n");
            sockfd = socket(AF_INET, SOCK_STREAM, 0);
            serv.sin_addr.s_addr = inet_addr(argv[1]);
            serv.sin_family = AF_INET;
            serv.sin_port = htons(6969);
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
                send_file(argv[1], 6969);
                break;
            case 2:
                recive_file(argv[1], 6969);
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
            serv.sin_addr.s_addr = inet_addr(argv[1]);
            serv.sin_family = AF_INET;
            serv.sin_port = htons(6969);
            memset(serv.sin_zero, 0, sizeof(serv.sin_zero));
            if (connect(sockfd2, (struct sockaddr *)&serv, sizeof(serv)) < 0)
            {
                perror("connect");
                exit(EXIT_FAILURE);
            }
            pthread_t videoSend, videoRec;

            pthread_create(&videoRec, NULL, &receive_video, &sockfd2);
            pthread_create(&videoSend, NULL, &send_video, &sockfd2);

            pthread_join(videoRec, NULL);
            pthread_join(videoSend, NULL);
            close(sockfd2);
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
            serv.sin_port = htons(6969);
        
            if (connect(sockfd, (struct sockaddr *)&serv, sizeof(serv)) < 0) {
                error("Error in connecting  ");
            }

            printf("Connected to the server\n");
            pthread_t audioRecv,audioSend;
            
            pthread_create(&audioSend,NULL,&audio_Send,&sockfd);
            // pthread_create(&audioRecv,NULL,&audio_Recv,&sockfd);
            
            pthread_join(audioSend,NULL);
            // pthread_join(audioRecv,NULL);
            close(sockfd);






            break;
        case 5:
            goto exiT;
        default:
        system("clear");
            printf("\033[0;31m");
            printf("[-1]not a valid choice\n");
            printf("\033[0m");
            while(getchar() !='\n'){}
            // while (getchar() != '\n')
            // {
            //     // Wait for Enter key to be pressed
            // }
            break;
        }
    }
exiT:

    return 0;
}
