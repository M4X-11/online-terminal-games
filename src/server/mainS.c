#include <stdio.h>
#include <unistd.h>
#include <sys/select.h>
#include <string.h>
#include "Snetwork.h"
#include "commands.h"
#include "playerState.h"
#include "gameHandler.h"
#include <stdlib.h>

Player players[MAX_PLAYERS] = {0};
int connected = 0;
int currentGameMode = 0; // 0 = none, 1 = snake, 2 = ttt

int initGame(int mode) {
    if (mode == 1) {
        printf("Starting Snake Game...\n");
        // Add logic to start Snake game
        sendMode(SNAKE);

    } else if (mode == 2) {
        printf("Starting Tic-Tac-Toe Game...\n");
        // Add logic to start Tic-Tac-Toe game
        sendMode(TTT);
    } else {
        printf("Invalid mode selected.\n");
    }
    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/time.h>

#include "Snetwork.h"
#include "commands.h"
#include "playerState.h"
#include "gameHandler.h"

Player players[MAX_PLAYERS] = {0};
int connected = 0;
int currentGameMode = 0; // 0 = none, 1 = snake, 2 = ttt

int initGame(int mode) {
    if (mode == 1) {
        printf("Starting Snake Game...\n");
        currentGameMode = 1;
        startMode(SNAKE);
    } else if (mode == 2) {
        printf("Starting Tic-Tac-Toe Game...\n");
        currentGameMode = 2;
        startMode(TTT);
    } else {
        printf("Invalid mode selected.\n");
    }
    return 0;
}

int main(void)
{
    int mode = 0;

    printf("Welcome to online terminal games\n");
    printf("snake[1]\nTicTacToe[2]\n");

    if (scanf("%d", &mode) == 1) {
        getchar(); // consume leftover newline
        initGame(mode);
    }

    startServer();

    while (1)
    {
        fd_set readfds;
        FD_ZERO(&readfds);

        // 1. Add STDIN (Keyboard) & Server Listening Socket
        FD_SET(STDIN_FILENO, &readfds);
        FD_SET(server_socket, &readfds);

        int max_fd = server_socket;
        if (STDIN_FILENO > max_fd) {
            max_fd = STDIN_FILENO;
        }

        // 2. Add Active Client Sockets
        for (int i = 0; i < MAX_PLAYERS; i++) {
            if (players[i].socket > 0) {
                FD_SET(players[i].socket, &readfds);
                if (players[i].socket > max_fd) {
                    max_fd = players[i].socket;
                }
            }
        }

        // 3. Define timeout (e.g., 50ms) so select() returns regularly
        struct timeval tv;
        tv.tv_sec = 0;
        tv.tv_usec = 50000; 

        int ret = select(max_fd + 1, &readfds, NULL, NULL, &tv);

        if (ret < 0) {
            perror("select");
            break;
        }

        // --- HANDLER A: KEYBOARD (STDIN) ---
        if (FD_ISSET(STDIN_FILENO, &readfds)) {
            char line[1024];

            if (fgets(line, sizeof(line), stdin) != NULL) {
                if (strcmp(line, "exit\n") == 0) {
                    break;
                }
                line[strcspn(line, "\n")] = '\0';
                if (strlen(line) > 0) {
                    char **toks = tokens(line);
                    cmd(toks);

                    for (int i = 0; toks[i] != NULL; i++) {
                        free(toks[i]);
                    }
                    free(toks);
                }
            }
        }

        // --- HANDLER B: NEW INCOMING CONNECTIONS ---
        if (FD_ISSET(server_socket, &readfds)) {
            int client = acceptPlayer(players, &connected);
            if (client >= 0) {
                printf("\nPlayer connected (%d/%d)\n", connected, MAX_PLAYERS);
            }
        }

        // --- HANDLER C: CLIENT NETWORK DATA ---
        for (int i = 0; i < MAX_PLAYERS; i++)
        {
            if (players[i].socket <= 0)
                continue;

            if (FD_ISSET(
                    players[i].socket,
                    &readfds))
            {
                int o = readPackage(
                    players[i].socket
                );

                printf(
                    "\nPlayer %d: %d\n",
                    i,
                    o
                );
                printf("OTG$ ");
                fflush(stdout);
            }
        }

        // --- HANDLER D: GAME TICK ---
        if (currentGameMode != 0) {
            gameLoop();
            printf("Game loop running for mode %d\n", currentGameMode);
        }
    }

    return 0;
}







/*
int main()
{
    int mode;

    printf("Welcome to online terminal games\n");
    printf("snake[1]\nTicTacToe[2]\n");

    scanf("%d", &mode);
    getchar();


    startServer();



    while (1)
    {
        fd_set readfds;

        FD_ZERO(&readfds);

        //
        //* Terminal
        //
        FD_SET(STDIN_FILENO, &readfds);

        //
        //Server socket = new connections
        //
        FD_SET(server_socket, &readfds);

        int max_fd = server_socket;

        if (STDIN_FILENO > max_fd)
            max_fd = STDIN_FILENO;

        //
        //* Existing players
        //
        for (int i = 0; i < MAX_PLAYERS; i++)
        {
            if (players[i].socket > 0)
            {
                FD_SET(players[i].socket, &readfds);

                if (players[i].socket > max_fd)
                    max_fd = players[i].socket;
            }
        }

        //
        //* Wait for something to happen.
        //
        int ret = select(
            max_fd + 1,
            &readfds,
            NULL,
            NULL,
            NULL
        );

        if (ret < 0)
        {
            perror("select");
            break;
        }

        //*
        //* =========================
        //* TERMINAL
        //* =========================
        //*

        if (FD_ISSET(STDIN_FILENO, &readfds))
        {
            char line[1024];

            printf("OTG$ ");
            fflush(stdout);

            if (fgets(line, sizeof(line), stdin) == NULL ||
                strcmp(line, "exit\n") == 0)
            {
                printf("\nBye\n");
                break;
            }

            if (line[0] == '\n')
                continue;

            line[strcspn(line, "\n")] = '\0';

            {
                char **toks = tokens(line);
                cmd(toks);

                // free tokenized input 
                for (int i = 0; toks[i] != NULL; i++)
                    free(toks[i]);
                free(toks);
            }
        }

        //*
        //* =========================
        //* NEW CONNECTION
        //* =========================
        //

        if (FD_ISSET(server_socket, &readfds))
        {
            int client = acceptPlayer(
                players,
                &connected
            );

            if (client >= 0)
            {
                printf(
                    "\nPlayer connected (%d/%d)\n",
                    connected,
                    MAX_PLAYERS
                );
            }
        }

        ///* =========================
        //* =========================
        //* PLAYER DATA
        //* =========================
        ///

        for (int i = 0; i < MAX_PLAYERS; i++)
        {
            if (players[i].socket <= 0)
                continue;

            if (FD_ISSET(
                    players[i].socket,
                    &readfds))
            {
                int o = readPackage(
                    players[i].socket
                );

                printf(
                    "\nPlayer %d: %d\n",
                    i,
                    o
                );
                printf("OTG$ ");
                fflush(stdout);
            }
        }
        ///////GAME LOOP
        if (currentGameMode != 0) {
            gameLoop();
            printf("Game loop running for mode %d\n", currentGameMode);
        }
    }


    return 0;
}*/