#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
void *send_messageServer(void *arg)
{
    printf("\033[0;32m");
    int newsockfd = *(int *)arg;
    char message[1024];
    while (1)
    {
        printf("\033[0;38m");
        fgets(message, 1024, stdin);
        printf("\033[0m");
        if (strcmp(message, "exit\n") == 0)
        {
            printf("\033[0;31m");
            printf("[-1]signing of\n");
            printf("\033[0m");
            exit(1);
        }

        send(newsockfd, message, strlen(message), 0);
    }
}

void *recv_messageServer(void *arg)
{
    int newsockfd = *(int *)arg;
    char buffer[1024] = {0};
    while (1)
    {
        int valread = recv(newsockfd, buffer, 1024, 0);
        printf("\033[0;32m");
        printf("\n                                                                                                %s", buffer);
        printf("\033[0m");
        memset(buffer, 0, sizeof(buffer));
    }
}
void *send_messageClient(void *arg)
{
    printf("Enter exit to exit");
    int newsockfd = *(int *)arg;
    char message[1024];
    while (1)
    {
        fgets(message, 1024, stdin);
        if (strcmp(message, "exit\n") == 0)
        {
            printf("\033[0;31m");
            printf("[-1]signing of\n");
            printf("\033[0m");
            exit(1);
        }
        send(newsockfd, message, strlen(message), 0);
    }
}
void *recv_messageClient(void *arg)
{
    printf("Enter exit to exit");
    int newsockfd = *(int *)arg;
    char buffer[1024] = {0};
    while (1)
    {
        int valread = recv(newsockfd, buffer, 1024, 0);
        printf("\033[0;32m");
        printf("\n                                                                                                %s", buffer);
        printf("\033[0m");
        memset(buffer, 0, sizeof(buffer));
    }
}