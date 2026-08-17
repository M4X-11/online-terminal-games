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
#include "../data.h"

int Sdispl()
{
    clear();

    mvprintw(0, 0, "Points: %d", packet.players[user.me].points);

    for (int i = 0; i < 47; i++)
        mvaddch(1, i, '#');

    for (int i = 0; i < 17; i++)
    {
        mvaddch(i + 2, 0, '#');
        mvaddch(i + 2, 46, '#');
    }

    for (int i = 0; i < 47; i++)
        mvaddch(19, i, '#');

    // Draw body
    for (int i=0; i<game.connections; i++){
        attron(COLOR_PAIR(i+1));
        for (int j = 0; j < packet.players[i].points; j++){
            mvaddch(game.players[i].snake.body[j].y + 2, game.players[i].snake.body[j].x + 1, '*');
            }
        attroff(COLOR_PAIR(i+1));
        }

    // Apple
    mvaddch(packet.apple->y + 2, packet.apple->x + 1, 'o');

    // Head
    for (int i=0; i<game.connections; i++){
        attron(COLOR_PAIR(i+1));
        mvaddch(game.players[i].snake.y + 2, game.players[i].snake.x + 1, '@');
        attroff(COLOR_PAIR(i+1));
    }
    
    if (packet.players[user.me].dead=='d'){
        mvprintw(20, 0, "DEAD");
    }


    //mvprintw(23, 0, "Package size: %d", bytes);
    mvprintw(21, 0, "Package size: %zu", sizeof(Packets));
    refresh();
    return 0;
}