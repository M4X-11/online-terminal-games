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
    //Address addr;
    printf("Welcome to online terminal games!\n");
    char e='t';
    
    while (e=='t')
    {
        printf("Enter server IP: ");
        fflush(stdout);

        if (fgets(addr.ip, sizeof(addr.ip), stdin)==NULL || strcmp(addr.ip, "exit\n")==0) {
            printf("\nBye\n");
            break;
        }



        if (addr.ip[0]=='\n') {
            continue;
        }
        
        addr.ip[strlen(addr.ip) -1] = '\0';
        e='f';
        
    }
    int result;
    do {
        printf("Enter server port: ");
        result = scanf("%d", &addr.port);

        if (result != 1) {
            printf("Invalid input. Please enter a number.\n");

            // Clear the invalid input from the buffer
            while (getchar() != '\n');
        }
    } while (result != 1);
    
    char n='t';
    
    while (n=='t')
    {
        getchar();
        printf("Enter an username: ");
        fflush(stdout);

        if (fgets(user.username, sizeof(user.username), stdin)==NULL || strcmp(user.username, "exit\n")==0) {
            printf("\nBye\n");
            break;
        }



        if (addr.ip[0]=='\n') {
            continue;
        }
        
        user.username[strlen(user.username) -1] = '\0';
        n='f';
        
    }

    //network
    startConnection();

    return 0;
}