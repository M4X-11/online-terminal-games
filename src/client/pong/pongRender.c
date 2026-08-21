#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <ncurses.h>
#include <arpa/inet.h>
#include "pongcom.h"
#include "../data.h"

int PongDispl()
{
    clear();

    mvprintw(0, 0, "Points: %d - %d", pong.player[0].score, pong.player[1].score);

    for (int i = 0; i < 47; i++)
        mvaddch(1, i, '#');

    for (int i = 0; i < 17; i++)
    {
        mvaddch(i + 2, 0, '#');
        mvaddch(i + 2, 46, '#');
    }

    for (int i = 0; i < 47; i++)
        mvaddch(19, i, '#');

    

    // ball
    mvaddch(pong.ball_x, pong.ball_y, 'o');

    int lenght=47;
    //int lenght=17;
    
    for (int i=0; i<9; i++){
        mvaddch(pong.player[0].y-8+i, 1, 'H');
    }
    for (int i=0; i<9; i++){
        mvaddch(pong.player[1].y-8+i, lenght-1, 'H');
    }
    
    


    //mvprintw(23, 0, "Package size: %d", bytes);
    mvprintw(21, 0, "Package size: %zu", sizeof(pong));
    refresh();
    return 0;
}