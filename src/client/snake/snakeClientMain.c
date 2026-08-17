#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <ncurses.h>
#include <arpa/inet.h>
#include "snakecom.h"


int me;
int bytes;
/*
int snakeKey(){

    int key = getch();
        

        switch (key)
        {
            case KEY_UP:
                if (game.players[me].snake.direction != DOWN)
                {
                    game.players[me].snake.direction = UP;
                }
                break;
            case KEY_DOWN:
                if (game.players[me].snake.direction != UP)
                {
                    game.players[me].snake.direction = DOWN;
                }
                break;
            case KEY_LEFT:
                if (game.players[me].snake.direction != RIGHT)
                {
                    game.players[me].snake.direction = LEFT;
                }
                break;
            case KEY_RIGHT:
                if (game.players[me].snake.direction != LEFT)
                {
                    game.players[me].snake.direction = RIGHT;
                }
                break;
        }

        clientPacket.dir=game.players[me].snake.direction;

        if (key != ERR){
            send(network_socket, &clientPacket, sizeof(clientPacket), 0);
        }
        
    return 0;
}*/




int snakeUpdate() {
    

    /*/create
    int network_socket;
    network_socket = socket(AF_INET, SOCK_STREAM, 0);

    //specify
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(6969);
    //server_address.sin_addr.s_addr = INADDR_ANY;
    inet_pton(AF_INET, "144.24.205.234", &server_address.sin_addr);

    //create connect
    int connection_status = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));
    while (connection_status ==-1) {
        connection_status = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));
        usleep(100000);
        
    }

    recv(network_socket, &me, sizeof(int), 0);*/



    

        //update snake head
            for (int i=0; i<game.connections; i++){
                game.players[i].snake.oldX = game.players[i].snake.x;
                game.players[i].snake.oldY = game.players[i].snake.y;
            }
        //get res
        
        //printf("\nsend: ");
        
        
        
        /*
        //recv(network_socket, &game, sizeof(game), 0);
        bytes = recvAll(network_socket, &packet, sizeof(packet));
        */
        for (int i=0; i<packet.connections; i++){
                game.players[i].snake.x = packet.players[i].x;
                game.players[i].snake.y = packet.players[i].y;
            }
        game.connections=packet.connections;
        
        //bytes = recv(network_socket, &game, sizeof(game), 0);

        // update snake body
            for (int i=0; i<game.connections; i++){
                for (int j = packet.players[i].points; j > 0; j--)
                    game.players[i].snake.body[j] = game.players[i].snake.body[j-1];

                game.players[i].snake.body[0].x = game.players[i].snake.oldX;
                game.players[i].snake.body[0].y = game.players[i].snake.oldY;
            }

        
        
        
        //printf("You entered: %s\n", line);
        //send(network_socket, &players[0].snake.direction, sizeof(players[0].snake.direction), 0);

    
    
    return 0;
}