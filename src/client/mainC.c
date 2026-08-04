#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>
//#include "common.h"
#include <time.h>

int main(){
    char* line[50];
    printf("Welcome to online terminal games\n");
    
    while (1)
    {
        printf("Enter server IP: ");
        fflush(stdout);

        if (fgets(line, sizeof(line), stdin)==NULL || strcmp(line, "exit\n")==0) {
            printf("\nBye\n");
            break;
        }



        if (line[0]=='\n') {
            continue;
        }
        
        line[strlen(line) -1] = '\0';
        
    }

    return 0;
}