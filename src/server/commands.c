#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#include "Snetwork.h"
#include "playerState.h"
#include "gameHandler.h"

//gamlist
#include "../../games/GameHeader.h"

#include "../../src/engineAPI.h"


int strt=0;
int ls=0;
int cmd(char** args) {

    /*
    if (strcmp(args[0], "test") == 0) { 
        for (int i = 0; i < TOTAL_GAMES; i++){
            if (ALL_GAMES[i]->cmd == NULL) {
                continue;
            }
            cmdManager *c = (cmdManager *)ALL_GAMES[i]->cmd();
            if (c == NULL) continue;
            if (c[0].command[0] == '\0') continue;
            printf("%s\n", c[0].command);
            fflush(stdout);
        }
        
    }*/

    for (int i = 0; i < TOTAL_GAMES; i++){
        if (strcmp(args[0], ALL_GAMES[i]->name) == 0){
            if (ALL_GAMES[i]->cmd == NULL) {
                continue;
            }
            cmdManager *c = (cmdManager *)ALL_GAMES[i]->cmd();
            if (c == NULL) continue;
            for (int j=0; j<6; j++){
                
                if (args[1] == NULL && c[j].command[0] != '\0'){
                    printf("%s\n", c[j].command);
                }else if (args[1] != NULL && strcmp(args[1], c[j].command) == 0){
                    c[j].funct();
                    break;
                }
            }
        }
    }

    
    if (args == NULL || args[0] == NULL) {
        return 0;
    }
    

    if (strcmp(args[0], "help") == 0) { 
        printf("Available commands:\n");
        for (int i = 0; i < TOTAL_GAMES; i++) {
            // Grab the pointer directly from the array!
            printf("  start %s - Start the %s game\n", ALL_GAMES[i]->name, ALL_GAMES[i]->name); 
        }
        printf("  ls players - List all connected players\n");
        printf("  kick <player_id> - Disconnect a player by their ID\n");
        printf("  restart - Restart the current game\n");
        fflush(stdout);
    }

    if (strcmp(args[0], "start") == 0) { 
        strt = 1; 
    }

    if (strcmp(args[0], "ls") == 0) { 
        ls = 1; 
    }

    if (strcmp(args[0], "start") == 0) { 
        if (args[1] == NULL) {
            printf("No game specified.\n");
            return 0;
        }
        if (current_game != NULL) {
            printf("A game is already running. Please restart or exit the current game first.\n");
            return 0;
        }
        for (int i = 0; i < TOTAL_GAMES; i++) {
            if (strcmp(args[1], ALL_GAMES[i]->name) == 0){
                if (connected < ALL_GAMES[i]->min_players) {
                    printf("Not enough players connected to start %s. Need at least %d player/s.\n", ALL_GAMES[i]->name, ALL_GAMES[i]->min_players);
                    return 0;
                }if (connected > ALL_GAMES[i]->max_players) {
                    printf("Too many players connected to start %s. Only %d players allowed.\n", ALL_GAMES[i]->name, ALL_GAMES[i]->max_players);
                    return 0;
                }
                printf("starting %s\n", ALL_GAMES[i]->name);
                startMode(i);
            }
        }
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
    //restart
    if (strcmp(args[0], "restart") == 0) { 
        
        if (current_game == NULL) {
            printf("No game is currently running. Cannot restart.\n");
            return 0;
        }
        restart();
    }
    if (strcmp(args[0], "end") == 0) { 
        
        if (current_game == NULL) {
            printf("No game is currently running. Cannot end.\n");
            return 0;
        }
        void cleanup();
        current_game = NULL;
        app_state = STATE_MENU;
        leaveMode();
    }
    
    ls=0;
    strt = 0;
    return 0;
}

char** tokens(char* args) {
    int num = strlen(args);
    
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
    
    res[o] = NULL;
    return res;
}
