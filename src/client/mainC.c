#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>
#include "data.h"
#include <time.h>

int main(){
    printf("Welcome to online terminal games!\n");
    char e='t';
    
    while (e=='t')
    {
        printf("Enter server IP: ");
        fflush(stdout);

        if (fgets(ip, sizeof(ip), stdin)==NULL || strcmp(ip, "exit\n")==0) {
            printf("\nBye\n");
            break;
        }



        if (ip[0]=='\n') {
            continue;
        }
        
        ip[strlen(ip) -1] = '\0';
        e='f';
        
    }

    return 0;
}