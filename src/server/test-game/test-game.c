#include "../gameHandler.h"
#include "../../engineAPI.h"

/* --- 1. WRITE YOUR NORMAL GAME FUNCTIONS --- */

static void snake_init() {
    // Reset snake length, spawn first apple
}

static void snake_update() {
    // Advance snake 1 step, check wall collisions
}



static void snake_input(int key, int i) {
    // Handle KEY_UP, KEY_DOWN, etc.
    (void)key;
    (void)i;
}


/* --- 2. PACKAGE THEM INTO THE MODULE STRUCT --- */

// Marking it 'extern' in a snake header (or passing &SNAKE_MODULE) exposes it
const GameMode SNAKE_MODULE = {
    .name         = "Snake",
    .init         = snake_init,    // Handing over function memory address
    .update       = snake_update,  // Handing over function memory address
    .input = snake_input    // Handing over function memory address
};