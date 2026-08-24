#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include "Snetwork.h"
#include "gameHandler.h"
#include <stdlib.h>
#include "snake/loop.h"
#include <time.h>
#include "pong/pongLoop.h"

///new api thing
#include "../../games/GameHeader.h"
///
#include "../engineAPI.h"


int running = 1;

AppState app_state = STATE_MENU;
const GameMode *current_game = NULL;
void *game_memory = NULL;

static void cleanup() {
    printf("[%s] exited!\n", current_game->name);
    app_state = STATE_MENU;
    current_game = NULL;
    desired_ms = 100000; // Reset to default update interval
}


// ============================================================================
// 2. GAME 1: SNAKE IMPLEMENTATION
// ============================================================================



static void snake_init() {
    //initSNAKE();
}

static void snake_update() {
    //SnakeGameLoop();
}

////////

static void snake_input(int input, int i){
    game.players[i].snake.direction=input;  
}






// Instantiate the Snake "Cartridge"
GameMode SnakeGame = {
    .name = "Snake",
    .init = snake_init,
    .update = snake_update,
    .input = snake_input,
    .cleanup = cleanup
};

// ============================================================================
// 2. GAME 2: PONG IMPLEMENTATION
// ============================================================================


static void pong_init() {
    InitPONG(); // Initialize Pong game state
}
static void pong_update() {
    PongGameLoop();
}

static void pong_input(int input, int i){
    pong.player[i].direction=input;
    playerMove(i, input);
    printf("player[%d] direction: %d\n", i, input);
}

GameMode PongGame = {
    .name = "Pong",
    .init = pong_init, // Implement Pong initialization
    .update = pong_update, // Implement Pong update logic
    .input = pong_input, // Implement Pong rendering
    .cleanup = cleanup // Implement Pong cleanup
};

////////////////

int restart(){
    printf("[%s] Restarted game!\n", current_game->name);
    current_game->init();
    return 0;
}

int startMode(int mode){
    sendMode(mode);

    
    current_game = ALL_GAMES[mode];
    current_game->init();
    app_state = STATE_IN_GAME;
            


    return 0;
}



int gameLoop(void)
{
    static struct timespec last_update = {0};
    struct timespec now;

    clock_gettime(CLOCK_MONOTONIC, &now);

    long elapsed_ms =
        (now.tv_sec - last_update.tv_sec) * 1000L +
        (now.tv_nsec - last_update.tv_nsec) / 1000000L;

    if (elapsed_ms >= 100) {
        //getData();
        last_update = now;
    }

    if (app_state == STATE_IN_GAME && current_game != NULL) {
        current_game->update();
        //current_game->render(game_memory);
    }

    return 0;
}



/*
int gameLoop(){
    AppState app_state = STATE_MENU;
    (void)app_state;
    GameMode *current_game = NULL; // Points to the active cartridge
    void *game_memory = NULL;       // Opaque pointer to active game state


    static struct timespec last_update = {0};
    struct timespec now;

    clock_gettime(CLOCK_MONOTONIC, &now);

    long elapsed_ms =
        (now.tv_sec - last_update.tv_sec) * 1000L +
        (now.tv_nsec - last_update.tv_nsec) / 1000000L;

    if (elapsed_ms >= 100)
    {
        // This code runs every 0.1 seconds
        getData();

        last_update = now;
    }
    
    //char input;

    
        
            // Render the active game frame
            //current_game->render(game_memory);

            //

            if (input == 'q') {
                // Exit game: Clean up memory and return to menu
                current_game->cleanup(game_memory);
                game_memory = NULL;
                current_game = NULL;
                app_state = STATE_MENU;
            } else {
                // Advance game logic by 1 input step
                current_game->update(game_memory, input);
            }
        
    current_game->update(game_memory);

    //getData();

    //printf("\nEngine terminated cleanly.\n");
    return 0;
}*/


/*
int initGmae(int mode) {
    if (mode == 1) {
        printf("Starting Snake Game...\n");
        // Add logic to start Snake game
        s

    } else if (mode == 2) {
        printf("Starting Tic-Tac-Toe Game...\n");
        // Add logic to start Tic-Tac-Toe game
    } else {
        printf("Invalid mode selected.\n");
    }
    return 0;
}

int gameMode(int mode) {
    if (mode == 1) {
        printf("Starting Snake Game...\n");
        // Add logic to start Snake game

    } else if (mode == 2) {
        printf("Starting Tic-Tac-Toe Game...\n");
        // Add logic to start Tic-Tac-Toe game
    } else {
        printf("Invalid mode selected.\n");
    }
    return 0;
}*/