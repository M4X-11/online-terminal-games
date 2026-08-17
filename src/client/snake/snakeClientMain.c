#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "snakecom.h"

int snakeUpdate() {
    // Update old head positions
    for (int i = 0; i < game.connections; i++) {
        game.players[i].snake.oldX = game.players[i].snake.x;
        game.players[i].snake.oldY = game.players[i].snake.y;
    }

    // Apply latest packet positions
    for (int i = 0; i < packet.connections; i++) {
        game.players[i].snake.x = packet.players[i].x;
        game.players[i].snake.y = packet.players[i].y;
    }

    game.connections = packet.connections;

    // Update snake bodies based on previous head positions
    for (int i = 0; i < game.connections; i++) {
        int points = packet.players[i].points;
        if (points > 0) {
            for (int j = points; j > 0; j--) {
                game.players[i].snake.body[j] = game.players[i].snake.body[j - 1];
            }
            game.players[i].snake.body[0].x = game.players[i].snake.oldX;
            game.players[i].snake.body[0].y = game.players[i].snake.oldY;
        }
    }

    return 0;
}
