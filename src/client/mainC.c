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

    //network
    startConnection();

    return 0;
}