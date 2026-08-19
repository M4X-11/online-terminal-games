#include <stdio.h>
#include <unistd.h>
#include <sys/select.h>
#include <string.h>
#include <stdlib.h>

#include "Snetwork.h"
#include "commands.h"
#include "playerState.h"
#include "gameHandler.h"


Player players[MAX_PLAYERS] = {0};
int connected = 0;

int currentGameMode = 0;
// 0 = none
// 1 = snake
// 2 = ttt


int initGame(int mode)
{
    if (mode == 1)
    {
        printf("Starting Snake Game...\n");

        currentGameMode = 1;

        sendMode(SNAKE);
    }
    else if (mode == 2)
    {
        printf("Starting Tic-Tac-Toe Game...\n");

        currentGameMode = 2;

        sendMode(TTT);
    }
    else
    {
        printf("Invalid mode selected.\n");
        return -1;
    }

    return 0;
}


int main()
{
    printf("Welcome to online terminal games\n\n");
    //printf("snake[1]\n");
    //printf("TicTacToe[2]\n");

    /*
     * If you don't actually need this local game selection,
     * you can remove this entire scanf section.
     */
    //int mode;

    //scanf("%d", &mode);
    //getchar();

    startServer();

    printf("OTG$ ");
    fflush(stdout);


    while (1)
    {
        fd_set readfds;

        FD_ZERO(&readfds);


        /*
         * =========================
         * TERMINAL
         * =========================
         */

        FD_SET(STDIN_FILENO, &readfds);


        /*
         * =========================
         * SERVER SOCKET
         * =========================
         */

        FD_SET(server_socket, &readfds);

        int max_fd = server_socket;

        if (STDIN_FILENO > max_fd)
            max_fd = STDIN_FILENO;


        /*
         * =========================
         * EXISTING PLAYERS
         * =========================
         */

        for (int i = 0; i < MAX_PLAYERS; i++)
        {
            if (players[i].socket > 0)
            {
                FD_SET(players[i].socket, &readfds);

                if (players[i].socket > max_fd)
                    max_fd = players[i].socket;
            }
        }


        /*
         * =========================
         * SELECT TIMEOUT
         * =========================
         *
         * Wake up every 50 ms even if
         * nobody sends anything.
         *
         * This is what allows gameLoop()
         * to continuously run.
         */

        struct timeval timeout;

        timeout.tv_sec = 0;
        timeout.tv_usec = 100000; // 50 ms// 100 ms


        /*
         * =========================
         * WAIT FOR I/O OR GAME TICK
         * =========================
         */

        int ret = select(
            max_fd + 1,
            &readfds,
            NULL,
            NULL,
            &timeout
        );


        if (ret < 0)
        {
            perror("select");
            break;
        }


        /*
         * =========================
         * TERMINAL INPUT
         * =========================
         */

        if (FD_ISSET(STDIN_FILENO, &readfds))
        {
            char line[1024];

            if (fgets(line, sizeof(line), stdin) == NULL)
            {
                printf("\nBye\n");
                break;
            }


            /*
             * Remove newline.
             */

            line[strcspn(line, "\n")] = '\0';


            /*
             * Exit command.
             */

            if (strcmp(line, "exit") == 0)
            {
                printf("\nBye\n");
                break;
            }


            /*
             * Ignore empty input.
             */

            if (line[0] == '\0')
            {
                printf("OTG$ ");
                fflush(stdout);
                continue;
            }


            /*
             * Tokenize command.
             */

            char **toks = tokens(line);


            if (toks != NULL)
            {
                cmd(toks);


                /*
                 * Free tokens.
                 */

                for (int i = 0; toks[i] != NULL; i++)
                    free(toks[i]);

                free(toks);
            }


            printf("OTG$ ");
            fflush(stdout);
        }


        /*
         * =========================
         * NEW CONNECTION
         * =========================
         */

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

                printf("OTG$ ");
                fflush(stdout);
            }
        }


        /*
         * =========================
         * PLAYER DATA
         * =========================
         */

        for (int i = 0; i < MAX_PLAYERS; i++)
        {
            if (players[i].socket <= 0)
                continue;


            if (FD_ISSET(
                    players[i].socket,
                    &readfds))
            {
                readPackage(
                    players[i].socket,
                    i
                );
                //printf("got data from player %d\n", i);
                fflush(stdout);
            }
        }


        /*
         * =========================
         * GAME LOOP
         * =========================
         *
         * This runs every ~50 ms while
         * a game is active.
         *
         * It does NOT depend on a player
         * sending data.
         */

        if (app_state == STATE_IN_GAME && current_game != NULL)
        {
            gameLoop();

            //printf("Game loop running\n");
            fflush(stdout);
        }
    }


    return 0;
}






































/*
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










//
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
        // Terminal
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
        // Existing players
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
        // Wait for something to happen.
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

        //
        // =========================
        // TERMINAL
        // =========================
        //

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

        //
        // =========================
        // NEW CONNECTION
        // =========================
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

        // =========================
        // =========================
        // PLAYER DATA
        // =========================
        //

        for (int i = 0; i < MAX_PLAYERS; i++)
        {
            if (players[i].socket <= 0)
                continue;

            if (FD_ISSET(
                    players[i].socket,
                    &readfds))
            {
                readPackage(
                    players[i].socket, i
                );

                
                printf("OTG$ ");
                fflush(stdout);
            }
        }
        ///////GAME LOOP
        printf("wtf");
        if (currentGameMode != 0) {
            gameLoop();
            printf("Game loop running for mode %d\n", currentGameMode);
        }
    }


    return 0;
}*/