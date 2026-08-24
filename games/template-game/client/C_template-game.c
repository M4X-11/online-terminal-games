#include "../../../src/engineAPI.h"
#include "../template-gameData.h"



static void template_init() {
    // initialize all game variable (will be the same code for restarting the game)
    // curs_set(0); // uncomment to make the typing cursor invisiible on the terminal
}

static void template_update() {
    // any client side game logic
}


//example - would be a struct
static int packetEXAMPLE;

// tell the engine what your network struct is
static void* template_net(void)
{
    static PacketManager P;
    P.payload = &packetEXAMPLE; // replace packetEXAMPLE with your actual packet pointer
    P.size = sizeof(packetEXAMPLE); //
    return &P;
}

static void template_render() {
    // your ncurses code
}



// defines your game functions and parameters
const GameMode TEMPLATE_MODULE = {
    .min_players = 99,
    .max_players = 100,
    .name         = "template",
    .init         = template_init,   
    .update       = template_update,  
    .net = template_net,   
    .render = template_render
};