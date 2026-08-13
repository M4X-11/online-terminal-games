#include <stdio.h>
#include <unistd.h>
#include <sys/select.h>
#include <string.h>
#include "Snetwork.h"
#include "commands.h"
#include "playerState.h"

Player players[MAX_PLAYERS] = {0};
int connected = 0;

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

        /*
        * Terminal
        */
        FD_SET(STDIN_FILENO, &readfds);

        /*
        * Server socket = new connections
        */
        FD_SET(server_socket, &readfds);

        int max_fd = server_socket;

        if (STDIN_FILENO > max_fd)
            max_fd = STDIN_FILENO;

        /*
        * Existing players
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
        * Wait for something to happen.
        */
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

        /*
        * =========================
        * TERMINAL
        * =========================
        */

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

            cmd(tokens(line));
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
                int o = readPackage(
                    players[i].socket
                );

                printf(
                    "\nPlayer %d: %d\n",
                    i,
                    o
                );
            }
        }
    }


    return 0;
}