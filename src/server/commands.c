#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int strt=0;
int cmd(char** args) {
    // If the user didn't type anything at all, safely exit
    if (args == NULL || args[0] == NULL) {
        return 0;
    }

    if (strcmp(args[0], "ls") == 0) { 
        printf("yoyoyooy\n"); 
    }
    
    // Safely check if a second argument actually exists before comparing it
    if (args[1] != NULL && strcmp(args[1], "ls") == 0) { 
        printf("yoyoyooy2\n"); 
    }

    if (strcmp(args[0], "echo") == 0) { 
        printf("yoyoyooy\n"); 
    }

    if (strcmp(args[0], "start") == 0) { 
        strt = 1; 
    }
    
    // Safely check if args[1] exists here too
    if (args[1] != NULL && strcmp(args[1], "snake") == 0 && strt == 1) { 
        printf("starting snake\n"); 
    }
    if (args[1] != NULL && strcmp(args[1], "ttt") == 0 && strt == 1) { 
        printf("starting TicTacToe\n"); 
    }
    

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