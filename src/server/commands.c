#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int mlw=0;
int idkvro(char** args) {
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

    if (strcmp(args[0], "mlw") == 0) { 
        mlw = 1; 
    }
    
    // Safely check if args[1] exists here too
    if (args[1] != NULL && strcmp(args[1], "setup") == 0 && mlw == 1) { 
        printf("setting up MLW\n"); 
    }

    mlw = 0;
    return 0;
}