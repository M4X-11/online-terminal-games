//declare all game filess
#include "template-game/template-gameData.h"
//etc

// Declare the module structs living in each game's file
extern const GameMode TEMPLATE_MODULE;
extern const GameMode SNAKE_MODULE;
//extern const GameMode PONG_MODULE;
//etc

// Package them into a single array
static const GameMode *ALL_GAMES[] = {
    &TEMPLATE_MODULE,
    &SNAKE_MODULE
    //&PONG_MODULE
    //etc
};

// Auto-calculate total games count
static const int TOTAL_GAMES = sizeof(ALL_GAMES) / sizeof(ALL_GAMES[0]);
