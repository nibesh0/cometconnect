#include "messagef/message.h"
#include "videof/videocall.h"
#include "filecon/fileshare.h"
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
        printf("Wellcome to gandu messaging Sservices\nChoose a option from bellow:-\n");
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
            int sockfd;
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
