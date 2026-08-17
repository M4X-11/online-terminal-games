#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Snetwork.h"
#include "playerState.h"
#include <errno.h>
#include "gameHandler.h"


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

    if (strcmp(args[0], "start") == 0) { 
        strt = 1; 
    }

    if (strcmp(args[0], "ls") == 0) { 
        ls = 1; 
    }
    
    // Safely check if args[1] exists here too
    if (args[1] != NULL && strcmp(args[1], "snake") == 0 && strt == 1) { 
        printf("starting snake\n");
        //sendMode(SNAKE);
        startMode(SNAKE);
        
    }
    if (args[1] != NULL && strcmp(args[1], "ttt") == 0 && strt == 1) { 
        printf("starting TicTacToe\n");
        //sendMode(TTT);
        startMode(TTT);
    }
    if (args[1] != NULL && strcmp(args[1], "players") == 0 && ls == 1) { 
        for (int i=0; i<(connected); i++){
            printf("\nplayer[%d]: %s\n", i, players[i].username);
        }
    }
    if (strcmp(args[0], "kick") == 0) { 
        if (args[1] == NULL){printf("no player id given\n"); return 0;}
        //int numid = args[1] - '0';
        char *end;
        long numid = strtol(args[1], &end, 10);

        if (*end != '\0')
        {
            printf("invalid player id\n");
            return 0;
        }

        if (numid < 0 || numid >= connected)
        {
            printf("invalid player id\n");
            return 0;
        }

        disconnectPlayer(players, (int)numid);
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
/*
int cmd(char** line){
    switch (expression)
    {
    case constant expression:
        // code
        break;
    
    default:
        break;
    }
}*/