#define MAX_PLAYERS 6

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

typedef struct {

    int x;
    int y;
} Segment;

typedef struct {

    int x;
    int y;
} Fire;

//Fire fire[20];

typedef struct {

    int x;
    int y;
    int oldX;
    int oldY;
    int points;
    int direction;
    Segment body[50];
    char ability;
} Snake;



typedef struct {
    int socket;
    Snake snake;
    int connected;
    char dead;
} SPlayer;

//Player players[MAX_PLAYERS];

typedef struct {

    int x;
    int y;
} AppleS;

//AppleS Apple[MAX_PLAYERS];

typedef struct {

    int dir;
    char ability;
} Cpacket;

extern Cpacket clientPacket;

typedef struct {

    AppleS apple[MAX_PLAYERS];
    SPlayer players[MAX_PLAYERS];
    int connections;
} Package;

extern Package game;
int Sdispl();
int snakeUpdate();

////////

typedef struct {
    
    int x;
    int y;
    int points;
    char dead;
    char ability;
    
} PlayerP;

typedef struct {
    AppleS apple[MAX_PLAYERS];
    PlayerP players[MAX_PLAYERS];
    int connections;
} Packets;
extern Packets packet;

//int me;