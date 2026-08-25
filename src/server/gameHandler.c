#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include "Snetwork.h"
#include "gameHandler.h"
#include <stdlib.h>

#include <time.h>


///new api thing
#include "../../games/GameHeader.h"
///
#include "../engineAPI.h"


int running = 1;

AppState app_state = STATE_MENU;
const GameMode *current_game = NULL;
void *game_memory = NULL;

void cleanup() {
    printf("[%s] exited!\n", current_game->name);
    app_state = STATE_MENU;
    current_game = NULL;
    desired_ms = 100000; // Reset to default update interval
}



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

