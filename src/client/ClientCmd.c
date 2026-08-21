#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"
//#include "playerState.h"
#include <errno.h>
//#include "gameHandler.h"


int strt=0;
int ls=0;
int cmd(char** args) {
    // If the user didn't type anything at all, safely exit
    if (args == NULL || args[0] == NULL) {
        return 0;
    }
    /*
    if (strcmp(args[0], "ls") == 0) { 
        printf("yoyoyooy\n"); 
    }
    
    // Safely check if a second argument actually exists before comparing it
    if (args[1] != NULL && strcmp(args[1], "ls") == 0) { 
        printf("yoyoyooy2\n"); 
    }

    if (strcmp(args[0], "echo") == 0) { 
        printf("yoyoyooy\n"); 
    }*/

    if (strcmp(args[0], "help") == 0) { 
        printf("Available commands:\n");
        printf("  vote snake - Vote to start the Snake game\n");
        printf("  vote ttt - Vote to start the Tic-Tac-Toe game\n");
        printf("  ls players - List all connected players\n");
    }

    if (strcmp(args[0], "vote") == 0) { 
        strt = 1; 
    }

    if (strcmp(args[0], "ls") == 0) { 
        ls = 1; 
    }
    
    if (args[1] != NULL && strcmp(args[1], "snake") == 0 && strt == 1) { 
        //printf("voting snake\n");
        strcpy(commandRES, "voting snake");
        sendVote(SNAKE);
    }
    if (args[1] != NULL && strcmp(args[1], "players") == 0 && ls == 1) { 
        listPlayers(network_socket);
        char buffer[1024];
        memset(buffer, 0, sizeof(buffer)); // Clear the buffer
        for (int i = 0; i < 6; i++) {
            if (players[i].socket > 0) {
                strcat(buffer, players[i].username);
                strcat(buffer, "  ");
                //printf("Player %d: %s\n", i, players[i].username);
            }
        }
        strcpy(commandRES, buffer);
    }
    
    
    ls=0;
    strt = 0;
    return 0;
}

char** tokens(char* args) {
    int num = strlen(args);
    // Allocate space (plus one extra for the trailing NULL pointer)
    char** res = malloc(sizeof(char*) * (num + 1)); 

    char* token = strtok(args, " ");
    int o = 0;
    while (token != NULL) {
        int y = strlen(token);
        res[o] = malloc(sizeof(char) * y + 1);
        strcpy(res[o], token);
        token = strtok(NULL, " ");
        o++;
    }
    
    res[o] = NULL; // <--- CRITICAL: Explicitly mark the end of the array
    return res;
}