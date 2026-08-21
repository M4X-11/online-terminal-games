


typedef struct {
    int y;
    int score;
    int dead;
    int direction; // Added to track the player's paddle movement direction and modify ball movement accordingly
}PLAYER;

typedef struct {
    PLAYER player[2];
    int ball_x;
    int ball_y;
}PONGPacket;

extern PONGPacket pong;
int PongDispl();

