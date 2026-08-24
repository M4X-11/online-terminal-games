#include <stdio.h>
#include "data.h"
#include "snake/snakecom.h"
//#include "gameHandler.h"
#include <ncurses.h>
#include <stdlib.h>
#include "pong/pongcom.h"

///new api thing
#include "../../games/GameHeader.h"
///
#include "../engineAPI.h"

int running = 1;

///snake
Packets packet;
Package game;
Cpacket clientPacket;
//pong
PONGPacket pong;
///general
AppState app_state;
const GameMode *current_game;
void *game_memory;


// ============================================================================
// 2. GAME 1: SNAKE IMPLEMENTATION
// ============================================================================



static void snake_init() {
    //printf("\n[Snake] Initialized game state!\n");
    //////
    /*
    initscr();
    cbreak();
    noecho();
    curs_set(0);

    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    start_color();
    init_pair(1, COLOR_RED,     COLOR_BLACK);
    init_pair(2, COLOR_GREEN,   COLOR_BLACK);
    init_pair(3, COLOR_YELLOW,  COLOR_BLACK);
    init_pair(4, COLOR_BLUE,    COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6, COLOR_CYAN,    COLOR_BLACK);
    init_pair(7, COLOR_WHITE,   COLOR_BLACK);*/
    curs_set(0);

}

static void snake_update() {
    snakeUpdate();
}

static void snake_render() {
    //printf("\n--- SNAKE GAME | Length: %d | Score: %d ---\n", s->length, s->score);
    //printf("Controls: Move (w/a/s/d) | Return to menu (q)\n");
    /* call the snake display function defined in snakeRender.c */
    Sdispl();
}

static void cleanup() {
    app_state = STATE_MENU;
    current_game = NULL;
    
    /* restore terminal state */
    //endwin();
}

/*
static void snake_net(void *state, int input) {
    SnakeState *s = (SnakeState *)state;
    (void)s;
    PacketHeader packet;
    packet.type=MSG_MOVE;
    packet.length=8;
    send_all(network_socket, &packet, sizeof(packet));
    send_all(network_socket, &input, sizeof(int));
}*/

// Instantiate the Snake "Cartridge"
GameMode SnakeGame = {
    .name = "Snake",
    .init = snake_init,
    .update = snake_update,
    .render = snake_render,
    .cleanup = cleanup
};

///pong
static void pong_init() {
    
    curs_set(0);

}
static void pong_render() {
    //printf("\n--- SNAKE GAME | Length: %d | Score: %d ---\n", s->length, s->score);
    //printf("Controls: Move (w/a/s/d) | Return to menu (q)\n");
    /* call the snake display function defined in snakeRender.c */
    PongDispl();
}
static void pong_update() {
    //nothing :3
}

GameMode PongGame = {
    .name = "Pong",
    .init = pong_init,
    .update = pong_update,
    .render = pong_render,
    .cleanup = cleanup
};


int startMode(int mode){

    
    current_game = ALL_GAMES[mode];
    current_game->init();
    app_state = STATE_IN_GAME;
            


    return 0;
}

int gameLoop(){
    //AppState app_state = STATE_MENU;
    (void)app_state;
    //GameMode *current_game = NULL; // Points to the active cartridge
    //void *game_memory = NULL;       // Opaque pointer to active game state

    
    

    
        if (current_game != NULL) {
            // Apply the newest game state before drawing so the screen
            // reflects the latest packet from the server.
            current_game->update();
            current_game->render();
        }else {
            displayMenu();
        }

    //printf("\nEngine terminated cleanly.\n");
    return 0;
}

int me(){
    return user.me;
}