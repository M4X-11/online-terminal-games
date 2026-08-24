#include "../../../src/engineAPI.h"
#include "../test-gameData.h"

/* --- 1. WRITE YOUR NORMAL GAME FUNCTIONS --- */

static void snake_init() {
    // Reset snake length, spawn first apple
}

static void snake_update() {
    // Advance snake 1 step, check wall collisions
}


//example - would be a struct
static int packetEXAMPLE;

// tell the engine what your network struct is
static void* snake_net(void)
{
    static PacketManager P;
    P.payload = &packetEXAMPLE;
    P.size = sizeof(packetEXAMPLE);
    return &P;
}

static void template_render() {
    
}

/* --- 2. PACKAGE THEM INTO THE MODULE STRUCT --- */

// Marking it 'extern' in a snake header (or passing &SNAKE_MODULE) exposes it
const GameMode TEMPLATE_MODULE = {
    .min_players = 99,
    .max_players = 100,
    .name         = "template",
    .init         = snake_init,    // Handing over function memory address
    .update       = snake_update,  // Handing over function memory address
    .net = snake_net,    // Handing over function memory address
    .render = template_render
};