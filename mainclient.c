#include "messagef/message.h"
#include "filecon/fileshare.h"
#include "videof/videocall.h"
// const char *logo =
//     "'   /$$      /$$/$$$$$$$$ /$$$$$$  /$$$$$$  /$$$$$$  /$$$$$$ /$$$$$$/$$   /$$ /$$$$$$       \n"
//     "'  | $$$    /$$| $$_____//$$__  $$/$$__  $$/$$__  $$/$$__  $|_  $$_| $$$ | $$/$$__  $$      \n"
//     "'  | $$$$  /$$$| $$     | $$  \\__| $$  \\__| $$  \\ $| $$  \\__/ | $$ | $$$$| $| $$  \\__/      \n"
//     "'  | $$ $$/$$ $| $$$$$  |  $$$$$$|  $$$$$$| $$$$$$$| $$ /$$$$ | $$ | $$ $$ $| $$ /$$$$      \n"
//     "'  | $$  $$$| $| $$__/   \\____  $$\\____  $| $$__  $| $$|_  $$ | $$ | $$  $$$| $$|_  $$      \n"
//     "'  | $$\\  $ | $| $$      /$$  \\ $$/$$  \\ $| $$  | $| $$  \\ $$ | $$ | $$\\  $$| $$  \\ $$      \n"
//     "'  | $$ \\/  | $| $$$$$$$|  $$$$$$|  $$$$$$| $$  | $|  $$$$$$//$$$$$| $$ \\  $|  $$$$$$/      \n"
//     "'  |__/     |__|________/\\______/ \\______/|__/  |__/\\______/|______|__/  \\__/\\______/       \n";

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
        // printf("\033[0;31m");
        // printf(logo);
        // printf("\033[0m");
        int choice;
        printf("Wellcome to messaging services\nChoose a option from bellow:-\n");
        printf("[1].Chatting\n");
        printf("[2].filesending\n");
        printf("[3].Videocall\n");
        printf("[4].Voicecall(voip)\n");
        printf("[5].Quit\n");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("chatting started...\n");
            int sockfd = socket(AF_INET, SOCK_STREAM, 0);
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
                send_file(argv[1],6969);
                break;
            case 2:
                recive_file(argv[1],6969);
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
            break;
        case 4:
            printf("voicecall\n");
            break;
        case 5:
            goto exiT;
        default:
            printf("\033[0;31m");
            printf("[-1]not a valid choice\n");
            printf("\033[0m");
            break;
        }
    }
exiT:

    return 0;
}
