#include <stdlib.h>
#include <stdint.h>
#ifndef ADDRESS_H
#define ADDRESS_H



typedef struct Player
{
    int socket;
    int connected;
    char username[20];
} PlayerNAMES;

extern PlayerNAMES players[6];

typedef struct {
    char ip[20];
    int port;
} Address;


typedef struct {
    char username[20];
    int me;
} Player;

extern Player user;

extern Address addr;

int Sdispl();

int startConnection();
int getData();
int send_all(int sock, const void *buffer, size_t length);
int sendDirection(int sock, int input);
////
extern int currentGameMode; // 0 = none, 1 = snake, 2 = ttt
extern int network_socket;
extern int running;

typedef enum
{
    SNAKE,
    TTT,
    PONG
} Gmode;

typedef enum
{
    MSG_LOGIN,
    MSG_CHAT,
    MSG_START_GAME,
    MSG_MOVE,
    MSG_PLAYER_LIST,
    MSG_VOTE,
    MSG_MODE,
    MSG_UPDATE_GAME,
    MSG_LEAVE
} MessageType;

typedef struct
{
    uint16_t type;
    uint16_t length;
} PacketHeader;

int sendVote(int vote);
int gameLoop();
int displayMenu();
void handleCommandInput(int key);
int listPlayers(int sock);

///////////////


/* 1. Define clean function pointer types using void* for game-private memory 
typedef void (*GameInitFunc)();
typedef void (*GameUpdateFunc)();
typedef void (*GameRenderFunc)();
typedef void (*GameCleanupFunc)();
typedef void* (*GameNetFunc)();

// 2. Package them into your engine's module struct 
typedef struct {
    const char *name;
    GameInitFunc    init;
    GameUpdateFunc  update;
    GameRenderFunc   render;
    GameCleanupFunc cleanup;
    GameNetFunc net;
} GameMode;*/


extern int cmdON;

int cmd(char** args, char** commandRES);

char** tokens(char* args);






/////
#endif

