#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void scanner(){
    char base_ip[16]; 
    int start = 1;  
    int end = 255;    

    printf("Enter the base IP address (e.g., 192.168.0.): ");
    scanf("%15s", base_ip);

    for (int i = start; i <= end; ++i) {
        char ip[16];
        char k[10];
        char command[50] = "ping -c 1 -W 1 ";
        
        snprintf(k, sizeof(k), "%d", i);
        strcat(base_ip, k);
        strcat(command, base_ip);
        strcat(command, " > /dev/null");

        int result = system(command);

        if (result == 0) {
            printf("IP address %s is up\n", base_ip);
        }

        base_ip[strlen(base_ip) - strlen(k)] = '\0';
    }

    return 0;
}
