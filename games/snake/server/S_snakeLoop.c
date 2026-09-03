#include "../../../src/engineAPI.h"
#include "S_snakecom.h"
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>

/* --- 1. WRITE YOUR NORMAL GAME FUNCTIONS --- */
static int connected;
//Player players[6];
Package game;
Packets packet;

static void appleRand(int *x, int *y)
{
    int min = 0;
    int Xmax = 45;
    int Ymax = 17;

    *x = (rand() % Xmax) + min;
    *y = (rand() % Ymax) + min;
}

static int isBodyAt(int x, int y, Segment body[], int bodyLength)
{
    for (int i = 0; i < bodyLength; i++) {
        if (body[i].x == x && body[i].y == y) {
            return 1;
        }
    }
    return 0;
}

static int isOutOfBounds(int x, int y)
{
    return (x == -1 || x == 45 || y == -1 || y == 17);
}


static void snake_init() {
    connected = connection_count();
    srand(time(NULL));

    appleRand(&game.apple[0].x, &game.apple[0].y);

    


    //init
    for (int i = 0; i < connected; i++) {
        appleRand(&game.players[i].snake.x,
                &game.players[i].snake.y);

        game.players[i].snake.oldX = game.players[i].snake.x;
        game.players[i].snake.oldY = game.players[i].snake.y;
        game.players[i].snake.direction = KEY_RIGHT;
        game.players[i].snake.points = 0;
        game.players[i].dead='a';
        packet.players[i].dead='a';
    }
    game.connections = connected;
}

static void snake_update() {
    for (int i = 0; i < connected; i++) {
            

            //update snake head
            for (int i=0; i<connected; i++){
                game.players[i].snake.oldX = game.players[i].snake.x;
                game.players[i].snake.oldY = game.players[i].snake.y;
            }
            for (int i=0; i<connected; i++){
                switch (game.players[i].snake.direction)
                {
                    case KEY_UP:
                        game.players[i].snake.y--;
                        break;
                    case KEY_DOWN:
                        game.players[i].snake.y++;
                        break;
                    case KEY_LEFT:
                        game.players[i].snake.x--;
                        break;
                    case KEY_RIGHT:
                        game.players[i].snake.x++;
                        break;
                }
            }

            // update snake body
            for (int i=0; i<connected; i++){
                for (int j = game.players[i].snake.points; j > 0; j--)
                    game.players[i].snake.body[j] = game.players[i].snake.body[j-1];

                game.players[i].snake.body[0].x = game.players[i].snake.oldX;
                game.players[i].snake.body[0].y = game.players[i].snake.oldY;
            }

            //apple
            

            for (int i=0; i<connected; i++){
                if (game.players[i].snake.x == game.apple[0].x &&
                    game.players[i].snake.y == game.apple[0].y)
                {
                    game.players[i].snake.points++;
                    game.players[i].snake.ability='f';//fireball

                    do {
                        appleRand(&game.apple[0].x, &game.apple[0].y);
                    } while (isBodyAt(game.apple[0].x,
                                    game.apple[0].y,
                                    game.players[i].snake.body,
                                    game.players[i].snake.points));
                }
            }
        
            //death
            for (int i=0; i<connected; i++){
                for (int j=0; j<connected; j++){
                    if ((isBodyAt(game.players[i].snake.x, game.players[i].snake.y, game.players[j].snake.body, game.players[j].snake.points)==1) || (isOutOfBounds(game.players[i].snake.x, game.players[i].snake.y))){
                        game.players[i].snake.x=-1000;
                        game.players[i].snake.y=-1000;
                        game.players[i].dead='d';
                        packet.players[i].dead='d';
                        //printf("player[%d] dead", i);
                        //fflush(stdout);
                    }
                }
            }

            //networking
            //packet optimization
            packet.apple[0].x=game.apple[0].x;
            packet.apple[0].y=game.apple[0].y;
            packet.connections=connected;
            
            
            // send game state
            for (int i=0; i<connected; i++){
                packet.players[i].points=game.players[i].snake.points;
                packet.players[i].x=game.players[i].snake.x;
                packet.players[i].y=game.players[i].snake.y;
                //send(game.players[i].socket, &packet, sizeof(packet), 0);
                //send(game.players[i].socket, &packet, sizeof(packet), 0);
                
                GameSend(i, &packet, sizeof(packet));
                /*
                PacketHeader header;
                header.type = MSG_UPDATE_GAME;
                header.length = sizeof(packet);
                send_all(game.players[i].socket, &header, sizeof(header));
                send_all(game.players[i].socket, &packet, sizeof(packet));
                */
            }
        
        }
}



static void snake_input(int key, int i) {
    // Handle KEY_UP, KEY_DOWN, etc.
    game.players[i].snake.direction=key; 
}


/* --- 2. PACKAGE THEM INTO THE MODULE STRUCT --- */

// Marking it 'extern' in a snake header (or passing &SNAKE_MODULE) exposes it
const GameMode SNAKE_MODULE = {
    .name         = "snake",
    .min_players = 1,
    .max_players = 6,
    .init         = snake_init,    // Handing over function memory address
    .update       = snake_update,  // Handing over function memory address
    .input = snake_input,    // Handing over function memory address
};