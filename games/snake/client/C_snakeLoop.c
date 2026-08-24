#include "../../../src/engineAPI.h"
#include "C_snakecom.h"
#include <ncurses.h>

/* --- 1. WRITE YOUR NORMAL GAME FUNCTIONS --- */

static void snake_init() {
    curs_set(0);
}

static void snake_update() {
    // Update old head positions
    for (int i = 0; i < game.connections; i++) {
        game.players[i].snake.oldX = game.players[i].snake.x;
        game.players[i].snake.oldY = game.players[i].snake.y;
    }
    
    // Apply latest packet positions
    for (int i = 0; i < packet.connections; i++) {
        game.players[i].snake.x = packet.players[i].x;
        game.players[i].snake.y = packet.players[i].y;
    }

    game.connections = packet.connections;

    // Update snake bodies based on previous head positions
    for (int i = 0; i < game.connections; i++) {
        int points = packet.players[i].points;
        if (points > 0) {
            for (int j = points; j > 0; j--) {
                game.players[i].snake.body[j] = game.players[i].snake.body[j - 1];
            }
            game.players[i].snake.body[0].x = game.players[i].snake.oldX;
            game.players[i].snake.body[0].y = game.players[i].snake.oldY;
        }
    }
}


//example - would be a struct


// tell the engine what your network struct is
static void* snake_net(void)
{
    static PacketManager P;
    P.payload = &packet;
    P.size = sizeof(packet);
    return &P;
}

static void snake_render() {
    clear();

    mvprintw(0, 0, "Points: %d", packet.players[me()].points);

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
    
    if (packet.players[me()].dead=='d'){
        mvprintw(20, 0, "DEAD");
    }


    //mvprintw(23, 0, "Package size: %d", bytes);
    mvprintw(21, 0, "Package size: %zu", sizeof(Packets));
    refresh();
}

/* --- 2. PACKAGE THEM INTO THE MODULE STRUCT --- */

// Marking it 'extern' in a snake header (or passing &SNAKE_MODULE) exposes it
const GameMode SNAKE_MODULE = {
    .min_players = 1,
    .max_players = 6,
    .name         = "snake",
    .init         = snake_init,    // Handing over function memory address
    .update       = snake_update,  // Handing over function memory address
    .net = snake_net,    // Handing over function memory address
    .render = snake_render
};