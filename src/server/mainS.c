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
    int mode;
    printf("Welcome to online terminal games\n");
    printf("\ngame modes:\nsnake[1]\nTicTacToe[2]");
    scanf("%d", mode);

    char line[1024];
    while (1)
    {
        printf("TOG$ ");
        fflush(stdout);

        if (fgets(line, sizeof(line), stdin)==NULL || strcmp(line, "exit\n")==0) {
            printf("\nBye\n");
            break;
        }



        if (line[0]=='\n') {
            continue;
        }
        
        line[strlen(line) -1] = '\0';
        printf("You entered: %s\n", line);
        //idkvro(line);
        //tokens(line);

        //idkvro(tokens(line));
    }

    return 0;
}