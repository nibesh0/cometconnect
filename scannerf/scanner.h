#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void scanner() {
    char ip_address[20];
    char command[100]; 

    printf("Enter the IP address to check: ");
    scanf("%s", ip_address);

    strcpy(command, "ping -c 1 ");
    strcat(command, ip_address);
    strcat(command,">/dev/null 2>&1");
    int status = system(command);
    if(status==0)
{

        printf("IP address is alive\n\n\n\n");
    }
    else 
    {
        printf("IP address is not reachable\n\n\n");
    }
sleep(2);
}
