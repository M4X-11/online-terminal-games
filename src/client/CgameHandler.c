#include <stdio.h>
#include "data.h"
#include "snake/snakecom.h"
//#include "gameHandler.h"
#include <ncurses.h>
#include <stdlib.h>

int running = 1;

///snake
Packets packet;
Package game;
Cpacket clientPacket;
///
AppState app_state;
GameMode *current_game;
void *game_memory;


// ============================================================================
// 2. GAME 1: SNAKE IMPLEMENTATION
// ============================================================================

typedef struct {
    int score;
    int length;
} SnakeState;

static void snake_init(void **state) {
    SnakeState *s = malloc(sizeof(SnakeState));
    s->score = 0;
    s->length = 3;
    *state = s; // Assign allocated memory back to generic pointer
    printf("\n[Snake] Initialized game state!\n");
    //////
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
    init_pair(7, COLOR_WHITE,   COLOR_BLACK);


}

static void snake_update(void *state) {
    SnakeState *s = (SnakeState *)state;
    (void)s;
    snakeUpdate();
}

static void snake_render(void *state) {
    SnakeState *s = (SnakeState *)state;
    (void)s;
    //printf("\n--- SNAKE GAME | Length: %d | Score: %d ---\n", s->length, s->score);
    //printf("Controls: Move (w/a/s/d) | Return to menu (q)\n");
    /* call the snake display function defined in snakeRender.c */
    Sdispl();
}

static void snake_cleanup(void *state) {
    free(state); // Free game-specific allocated state
    printf("[Snake] Cleaned up memory!\n");
    /* restore terminal state */
    endwin();
}

static void snake_net(void *state, int input) {
    SnakeState *s = (SnakeState *)state;
    (void)s;
    PacketHeader packet;
    packet.type=MSG_MOVE;
    packet.length=8;
    send_all(network_socket, &packet, sizeof(packet));
    send_all(network_socket, &input, sizeof(int));
}

// Instantiate the Snake "Cartridge"
GameMode SnakeGame = {
    .name = "Snake",
    .init = snake_init,
    .update = snake_update,
    .render = snake_render,
    .cleanup = snake_cleanup,
    .network = snake_net
};


int startMode(int mode){
    //sendMode(mode);

    if (mode == SNAKE) {
                current_game = &SnakeGame;
                current_game->init(&game_memory); // Allocate game state
                app_state = STATE_IN_GAME;
            } 
            /*else if (mode == TTT) {
                current_game = &TicTacToeGame;
                current_game->init(&game_memory); // Allocate game state
                app_state = STATE_IN_GAME;
            }*/
            else if (mode == 'x') {
                running = 0;
            }


    return 0;
}

int gameLoop(){
    //AppState app_state = STATE_MENU;
    (void)app_state;
    //GameMode *current_game = NULL; // Points to the active cartridge
    //void *game_memory = NULL;       // Opaque pointer to active game state

    
    

    
        if (current_game != NULL) {
            // Render the active game frame
            current_game->render(game_memory);

            

                // Advance game logic by 1 input step
                current_game->update(game_memory);
        }
            
            getData();
        
    

    //printf("\nEngine terminated cleanly.\n");
    return 0;
}