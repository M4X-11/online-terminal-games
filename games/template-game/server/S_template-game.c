#include "../../../src/engineAPI.h"
#include <stdio.h>
#include <ncurses.h>


static void snake_init() {
    // initialize all game variable (will be the same code for restarting the game)
}

static void snake_update() {
    // your main game logic
    // use "GameSend(i, &packet);" in a for loop to send the new gamestate at the end of the function
}



static void snake_input(int key, int i) {
    // Handle KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_SPACE.
    (void)key;
    (void)i;
}


///
// Custom server commands (6 max)
static void example(){
    printf("hello this is an example command\n");
}

static void bye(){
    printf("Goodbye!\n");
}

static void* snake_cmd(){
    static cmdManager c[] ={{
        .command="hello",
        .comment="says hello",
        .funct = example
    },{
        .command="bye",
        .comment="says goodbye",
        .funct= bye
    }};
    return c;
}
//////



// defines your game functions and parameters
const GameMode TEMPLATE_MODULE = {
    .name         = "template",
    .min_players = 99,
    .max_players = 100,
    .init         = snake_init,
    .update       = snake_update,
    .input = snake_input,
    .cmd = snake_cmd
};