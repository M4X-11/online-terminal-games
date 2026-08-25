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

extern int network_socket;



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






int cmd(char** args, char** commandRES);

char** tokens(char* args);






/////
#endif

