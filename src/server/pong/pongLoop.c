#include "pongLoop.h"
#include <time.h>
#include <stdlib.h>


int width;
int leght;

PONGPacket pong;

typedef struct
{
    float x;
    float y;
}BALLMOV;
BALLMOV ballMovement;




void ballRand(float *x, float *y)
{
    *x = (float)rand() / (float)RAND_MAX;
    *y = (float)rand() / (float)RAND_MAX;
}

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

int PongGameLoop()
{
    // Update ball position based on its movement vector
    pong.ball_x += (int)(ballMovement.x * 2); // Adjust speed as needed
    pong.ball_y += (int)(ballMovement.y * 2); // Adjust speed as needed

    // Check for collisions with top and bottom walls
    if (pong.ball_y <= 0 || pong.ball_y >= width - 1)
    {
        ballMovement.y = -ballMovement.y; // Reverse vertical direction
    }

    // Check for collisions with paddles
    if ((pong.ball_x == 1 && pong.ball_y >= pong.player[0].y - 1 && pong.ball_y <= pong.player[0].y + 1) ||
        (pong.ball_x == leght - 2 && pong.ball_y >= pong.player[1].y - 1 && pong.ball_y <= pong.player[1].y + 1))
    {
        ballMovement.x = -ballMovement.x; // Reverse horizontal direction
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



