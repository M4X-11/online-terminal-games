#ifndef PLAYERSTATE_H
#define PLAYERSTATE_H

#define MAX_PLAYERS 6

extern int currentGameMode; // 0 = none, 1 = snake, 2 = ttt

typedef struct Player
{
    int socket;
    int connected;
    char username[20];
} Player;

extern Player players[MAX_PLAYERS];



#endif