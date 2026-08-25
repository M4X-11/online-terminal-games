#include <stdio.h>
#include "data.h"

//#include "gameHandler.h"
#include <ncurses.h>
#include <stdlib.h>


///new api thing
#include "../../games/GameHeader.h"
///
#include "../engineAPI.h"




///general
AppState app_state;
const GameMode *current_game;
void *game_memory;









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