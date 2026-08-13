

#ifndef ADDRESS_H
#define ADDRESS_H

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
int startConnection();

////


typedef enum
{
    MSG_LOGIN,
    MSG_CHAT,
    MSG_START_GAME,
    MSG_MOVE,
    MSG_PLAYER_LIST,
    MSG_VOTE
} MessageType;

typedef struct
{
    uint16_t type;
    uint16_t length;
} PacketHeader;

int sendVote(int vote);
#endif

