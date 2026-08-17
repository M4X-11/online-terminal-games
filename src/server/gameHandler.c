#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include "Snetwork.h"
#include "gameHandler.h"
#include <stdlib.h>
#include "snake/loop.h"
#include <time.h>


int running = 1;

AppState app_state = STATE_MENU;
GameMode *current_game = NULL;
void *game_memory = NULL;


// ============================================================================
// 2. GAME 1: SNAKE IMPLEMENTATION
// ============================================================================

typedef struct {
    int score;
    int length;
} SnakeState;

static void snake_init(void **state) {
    SnakeState *s = malloc(sizeof(SnakeState));
    initSNAKE();
    *state = s;
}

static void snake_update(void *state) {
    SnakeState *s = (SnakeState *)state;
    SnakeGameLoop();
    (void)s;
}

static void snake_render(void *state) {
    SnakeState *s = (SnakeState *)state;
    printf("\n--- SNAKE GAME | Length: %d | Score: %d ---\n", s->length, s->score);
    printf("Controls: Move (w/a/s/d) | Return to menu (q)\n");
}

static void snake_cleanup(void *state) {
    free(state); // Free game-specific allocated state
    printf("[Snake] Cleaned up memory!\n");
}

// Instantiate the Snake "Cartridge"
GameMode SnakeGame = {
    .name = "Snake",
    .init = snake_init,
    .update = snake_update,
    .render = snake_render,
    .cleanup = snake_cleanup
};

////////////////

int startMode(int mode){
    sendMode(mode);

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

int gameLoop(void)
{
    static struct timespec last_update = {0};
    struct timespec now;

    clock_gettime(CLOCK_MONOTONIC, &now);

    long elapsed_ms =
        (now.tv_sec - last_update.tv_sec) * 1000L +
        (now.tv_nsec - last_update.tv_nsec) / 1000000L;

    if (elapsed_ms >= 100) {
        getData();
        last_update = now;
    }

    if (app_state == STATE_IN_GAME && current_game != NULL) {
        current_game->update(game_memory);
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
            }//
        
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