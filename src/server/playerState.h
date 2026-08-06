#ifndef PLAYERSTATE_H
#define PLAYERSTATE_H

#define MAX_PLAYERS 6

typedef struct Player
{
    int socket;
    int connected;
} Player;

extern Player players[MAX_PLAYERS];

#endif