
#include "playerState.h"
#include <stdint.h>
#ifndef SNETWORK_H
#define SNETWORK_H

//typedef struct Player Player;

extern int server_socket;
extern int connected;

int startServer();
int acceptPlayer(Player *players, int *connected);
int disconnectPlayer(Player *players, int id);

int recv_all(int sock, void *buffer, size_t length);
int send_all(int sock, const void *buffer, size_t length);

int readPackage(int sock);

int getData();

int sendMode(int mode);

typedef enum
{
    MSG_LOGIN,
    MSG_CHAT,
    MSG_START_GAME,
    MSG_MOVE,
    MSG_PLAYER_LIST,
    MSG_VOTE,
    MSG_MODE,
    MSG_UPDATE_SNAKE
} MessageType;

typedef enum
{
    SNAKE,
    TTT
} Gmode;

typedef struct
{
    uint16_t type;
    uint16_t length;
} PacketHeader;

#endif