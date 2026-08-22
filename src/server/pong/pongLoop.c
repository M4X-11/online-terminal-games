#include "pongLoop.h"
#include <time.h>
#include <stdlib.h>
#include "../gameHandler.h"
#include "../Snetwork.h"
#include <math.h>


int width=17;
int leght=47;

PONGPacket pong;

typedef struct
{
    float x;
    float y;
}BALLMOV;
BALLMOV ballMovement;

#define PI 3.14159265358979323846f
#define BALL_SPEED 1.0f // Adjust speed as needed

void ballRand(float *x, float *y)
{
    // Generate a random angle between 0 and 2*PI
    float angle = ((float)rand() / (float)RAND_MAX) * 2.0f * PI;

    // Optional: Avoid purely vertical launches (which cause infinite loops)
    // You can restrict angles to e.g., +/- 45 degrees relative to left/right

    *x = cosf(angle) * BALL_SPEED;
    *y = sinf(angle) * BALL_SPEED;
}

/*
void ballRand(float *x, float *y)
{
    *x = (float)rand() / (float)RAND_MAX;
    *y = (float)rand() / (float)RAND_MAX;
}*/

int InitPONG()
{
    srand(time(NULL));
    
    
    ballRand(&ballMovement.x, &ballMovement.y);

    pong.ball_x=leght/2;
    pong.ball_y=width/2;
    
    pong.player[0].y=width/2;
    pong.player[1].y=width/2;
    pong.player[0].score=0;
    pong.player[1].score=0;
    
    return 0;
}

int rePONG()
{
    
    
    ballRand(&ballMovement.x, &ballMovement.y);

    pong.ball_x=leght/2;
    pong.ball_y=width/2;
    
    pong.player[0].y=width/2;
    pong.player[1].y=width/2;
    
    return 0;
}

int setPONG(int w, int l)
{
    width=w;
    leght=l;
    return 0;
}


int paddleHitbox(int player, int thing){
    for (int i=0; i<9; i++){
        if (player-4+i==thing){
            return 1;
        }
    }
    return 0;
}

int paddleBallBox(int player, int thing){
    // Check for collisions with paddles
    for (int i=0; i<9; i++){
        if (player-4+i==thing){
            return 1;
        }
    }
    return 0;
}


int playerMove(int player, int direction)
{
    if (player < 0 || player > 1)
        return -1; // Invalid player index

    if (direction == UP)
    {
        pong.player[player].y--;
        pong.player[player].direction = UP;
    }
    else if (direction == DOWN)
    {
        pong.player[player].y++;
        pong.player[player].direction = DOWN;
    }

    // Ensure the paddle stays within bounds
    if (pong.player[player].y < 4)
        pong.player[player].y = 4;
    else if (pong.player[player].y > width - 2)
        pong.player[player].y = width - 2;

    return 0;
}

int PongGameLoop()
{
    // Update ball position based on its movement vector
    pong.ball_x += (ballMovement.x * 2); // Adjust speed as needed
    pong.ball_y += (ballMovement.y * 2); // Adjust speed as needed

    // Check for collisions with top and bottom walls
    if (pong.ball_y <= 0 || pong.ball_y >= width - 1)
    {
        ballMovement.y = -ballMovement.y; // Reverse vertical direction
    }

    /* Check for collisions with paddles
    if ((pong.ball_x <= 2 && pong.ball_y >= pong.player[0].y - 1 && pong.ball_y <= pong.player[0].y + 1) ||
        (pong.ball_x >= leght - 3 && pong.ball_y >= pong.player[1].y - 1 && pong.ball_y <= pong.player[1].y + 1))
    {
        ballMovement.x = -ballMovement.x; // Reverse horizontal direction
    }*/
    // Check collision using the full paddle range (+/- 4) and continuous x-position depth
    int hitPlayer1 = (pong.ball_x <= 2.5f) && 
                    (pong.ball_y >= pong.player[0].y - 4) && 
                    (pong.ball_y <= pong.player[0].y + 4);

    int hitPlayer2 = (pong.ball_x >= (leght - 3.5f)) && 
                    (pong.ball_y >= pong.player[1].y - 4) && 
                    (pong.ball_y <= pong.player[1].y + 4);

    if ((hitPlayer1 && ballMovement.x < 0) || (hitPlayer2 && ballMovement.x > 0))
    {
        ballMovement.x = -ballMovement.x; // Reverse direction
    }

    // Check for scoring
    if (pong.ball_x <= 0)
    {
        pong.player[1].score++;
        rePONG(); // Reset the game after a score
    }
    else if (pong.ball_x >= leght - 1)
    {
        pong.player[0].score++;
        rePONG(); // Reset the game after a score
    }


    //network

    
    PacketHeader header;
    header.type = MSG_UPDATE_PONG;
    header.length = sizeof(pong);
    send_all(players[0].socket, &header, sizeof(header));
    send_all(players[0].socket, &pong, sizeof(pong));
    send_all(players[1].socket, &header, sizeof(header));
    send_all(players[1].socket, &pong, sizeof(pong));

    return 0;
}

/*
int PongGameLoop()
{
    // Update ball position based on its movement vector
    pong.ball_x += (int)(ballMovement.x * 2); // Adjust speed as needed
    pong.ball_y += (int)(ballMovement.y * 2);

    // Check for collisions with top and bottom walls
    if (pong.ball_y <= 0 || pong.ball_y >= width - 1)
    {
        ballMovement.y = -ballMovement.y; // Reverse vertical direction
    }

    // Check for collisions with paddles
    if (pong.ball_x == 1) // Left paddle
    {
        if (pong.ball_y >= pong.player[0].y - 1 && pong.ball_y <= pong.player[0].y + 1)
        {
            ballMovement.x = -ballMovement.x; // Reverse horizontal direction
            if (pong.player[0].direction == UP)
            {
                ballMovement.y -= 0.5; // Adjust vertical movement based on paddle direction
            }
            else if (pong.player[0].direction == DOWN)
            {
                ballMovement.y += 0.5; // Adjust vertical movement based on paddle direction
            }
        }
        else
        {
            pong.player[1].score++; // Right player scores
            initPONG();             // Reset game state
        }
    }
    else if (pong.ball_x == leght - 2) // Right paddle
    {
        if (pong.ball_y >= pong.player[1].y - 1 && pong.ball_y <= pong.player[1].y + 1)
        {
            ballMovement.x = -ballMovement.x; // Reverse horizontal direction
        }
        else
        {
            pong.player[0].score++; // Left player scores
            initPONG();             // Reset game state
        }
    }

    return 0;
}*/



