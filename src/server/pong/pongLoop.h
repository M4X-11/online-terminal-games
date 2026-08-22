

typedef struct {
    int y;
    int score;
    int dead;
    int direction; // Added to track the player's paddle movement direction and modify ball movement accordingly
}PLAYER;


typedef struct {
    PLAYER player[2];
    float ball_x;
    float ball_y;
}PONGPacket;

extern PONGPacket pong;

int InitPONG();
int PongGameLoop();
int playerMove(int player, int direction);
