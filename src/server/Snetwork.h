
#include "playerState.h"
#ifndef SNETWORK_H
#define SNETWORK_H

//typedef struct Player Player;

extern int server_socket;
extern int connected;

int startServer();
int acceptPlayer(Player *players, int *connected);
int disconnectPlayer(int id);

#endif