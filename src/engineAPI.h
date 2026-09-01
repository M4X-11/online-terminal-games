#ifndef ENGINE_API_H
#define ENGINE_API_H

#include <stddef.h>

/* Function pointer types */
typedef void (*GameInitFunc)(void);
typedef void (*GameUpdateFunc)(void);
typedef void (*GameInputFunc)(int input, int i);
typedef void (*GameCleanupFunc)(void);
typedef void (*GameRenderFunc)(void);
typedef void *(*GameNetFunc)(void);
typedef void *(*GameCmdFunc)(void);

/* Game module */
typedef struct {
    const char *name;
    const int min_players;
    const int max_players;

    GameInitFunc init;
    GameUpdateFunc update;
    GameInputFunc input;
    GameRenderFunc render;
    GameCleanupFunc cleanup;
    GameNetFunc net;
    GameCmdFunc cmd;
} GameMode;

extern const GameMode *current_game;

/* Packet handling */
typedef struct {
    size_t size;
    void *payload;
} PacketManager;

/* Direction */
enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

/* Application state */
typedef enum {
    STATE_MENU,
    STATE_IN_GAME
} AppState;

extern AppState app_state;
/*
typedef struct Player
{
    int socket;
    int connected;
    char username[20];
} Player;
//temp
#define MAX_PLAYERS 6
extern Player players[MAX_PLAYERS];*/

int GameSend(int i, void *data, size_t p);
int connection_count();
int me();



typedef void (*cmdFunc)(void);
typedef struct {
    char command[10];
    char comment[20];


    size_t size;
    cmdFunc funct;
} cmdManager;


#endif /* ENGINE_API_H */