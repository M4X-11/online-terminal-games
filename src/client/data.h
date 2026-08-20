
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
    TTT
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
    MSG_UPDATE_SNAKE,
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

///////////////
typedef struct {
    const char *name;
    
    // Function pointers matching the game lifecycle
    void (*init)(void **state);
    void (*update)(void *state);
    void (*render)(void *state);
    void (*cleanup)(void *state);
    void (*network)(void *state, int input);
} GameMode;

typedef enum {
    STATE_MENU,
    STATE_IN_GAME
} AppState;

extern AppState app_state;
extern GameMode *current_game;
extern void *game_memory;

extern int cmdON;

int cmd(char** args);

char** tokens(char* args);

extern char commandRES[30];

/////
#endif

