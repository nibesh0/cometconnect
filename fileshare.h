#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

void recive_file(const char ipAdd[],int PORT)
{
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {'\0'};
    char path[100];

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        exit(1);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, ipAdd, &serv_addr.sin_addr) <= 0)
    {
        printf("\nInvalid address/ Address not supported \n");
        exit(1);
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        exit(1);
    }
    recv(sock, path, 100, 0);
    printf("%s", path);
    FILE *file = fopen(path, "wb");
    if (file == NULL)
    {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    size_t n;
    while ((n = recv(sock, buffer, sizeof(buffer), 0)) > 0)
    {
        if (fwrite(buffer, 1, n, file) != n)
        {
            perror("fwrite");
            exit(EXIT_FAILURE);
        }
    }

    close(sock);
    fclose(file);
}
void send_file(const char ipAddr[],int PORT)
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char path[100];

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(ipAddr);
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    printf("enter the file name\n");
    scanf("%s", path);
    FILE *file = fopen(path, "rb");
    if (file == NULL)
    {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    send(new_socket, path, 100, 0);
    size_t n;
    while ((n = fread(buffer, 1, sizeof(buffer), file)) > 0)
    {
        if (send(new_socket, buffer, n, 0) != n)
        {
            perror("send");
            exit(EXIT_FAILURE);
        }
    }

    close(new_socket);
    close(server_fd);
    fclose(file);
}