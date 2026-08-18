#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>
#include "loop.h"
#include <time.h>
#include "../Snetwork.h"
#include "playerState.h"

int mode;
//int server_socket;

int gameStarted = 0;
char abilityMode;

Package game;
Packets packet;
Cpacket clientPacket;

/*
int snakeRestart(){
    initSNAKE();
    return 0;
}*/

void appleRand(int *x, int *y)
{
    int min = 0;
    int Xmax = 45;
    int Ymax = 17;

    *x = (rand() % Xmax) + min;
    *y = (rand() % Ymax) + min;
}

int initSNAKE()
{
    srand(time(NULL));
    
    
    appleRand(&game.apple[0].x, &game.apple[0].y);

    for (int i=0; i<connected; i++){
        game.players[i].socket = players[i].socket;
        game.players[i].connected = players[i].connected;
    }
    //init
    for (int i = 0; i < connected; i++) {
        appleRand(&game.players[i].snake.x,
                &game.players[i].snake.y);

        game.players[i].snake.oldX = game.players[i].snake.x;
        game.players[i].snake.oldY = game.players[i].snake.y;
        game.players[i].snake.direction = RIGHT;
        game.players[i].snake.points = 0;
        game.players[i].dead='a';
        packet.players[i].dead='a';
    }
    game.connections = connected;
    
    return 0;
}

int isBodyAt(int x, int y, Segment body[], int bodyLength)
{
    for (int i = 0; i < bodyLength; i++) {
        if (body[i].x == x && body[i].y == y) {
            return 1;
        }
    }
    return 0;
}

int isOutOfBounds(int x, int y)
{
    return (x == -1 || x == 45 || y == -1 || y == 17);
}

int SnakeGameLoop()
{
    





    //printf("\nStarting game with %d players!\n", connected);

    

    

    //init

    


    // GAME LOOP
    
        
        /*
        if (FD_ISSET(STDIN_FILENO, &readfds))
        {
            char cmd[100];

            fgets(cmd, sizeof(cmd), stdin);
            
            if (strcmp(cmd, "restart\n") == 0)
            {
                printf("Restarting game...\n");

                // Reset every player
                for (int i = 0; i < connected; i++)
                {
                    appleRand(&game.players[i].snake.x,
                            &game.players[i].snake.y);

                    game.players[i].snake.oldX = game.players[i].snake.x;
                    game.players[i].snake.oldY = game.players[i].snake.y;
                    game.players[i].snake.points = 0;
                    game.players[i].snake.direction = RIGHT;
                    game.players[i].dead = 'a';
                    packet.players[i].dead = 'a';

                    memset(game.players[i].snake.body,
                        0,
                        sizeof(game.players[i].snake.body));
                }

                appleRand(&game.apple[0].x, &game.apple[0].y);
            }
        }*/

        for (int i = 0; i < connected; i++) {
            /*
            if (FD_ISSET(game.players[i].socket, &readfds)) {

                int dir;
                int n = recv(game.players[i].socket,
                            &clientPacket,
                            sizeof(clientPacket),
                            0);

                if (n > 0) {
                    game.players[i].snake.direction = clientPacket.dir;
                    printf("player[%d] direction: %d\n", i, clientPacket.dir);
                }
                else if (n == 0) {
                    printf("Player %d disconnected\n", i);
                    close(game.players[i].socket);
                    game.players[i].connected = 0;
                }
            }}*/

            //update snake head
            for (int i=0; i<connected; i++){
                game.players[i].snake.oldX = game.players[i].snake.x;
                game.players[i].snake.oldY = game.players[i].snake.y;
            }
            for (int i=0; i<connected; i++){
                switch (game.players[i].snake.direction)
                {
                    case UP:
                        game.players[i].snake.y--;
                        break;
                    case DOWN:
                        game.players[i].snake.y++;
                        break;
                    case LEFT:
                        game.players[i].snake.x--;
                        break;
                    case RIGHT:
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
                        printf("player[%d] dead", i);
                        fflush(stdout);
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

                PacketHeader header;
                header.type = MSG_UPDATE_SNAKE;
                header.length = sizeof(packet);
                send_all(game.players[i].socket, &header, sizeof(header));
                send_all(game.players[i].socket, &packet, sizeof(packet));
                printf("packet sent to player[%d]\n", i);
            }
        
        }


    

    return 0;
}