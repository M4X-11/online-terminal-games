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
        printf("OTG$ ");
        fflush(stdout);
        fd_set readfds;

        FD_ZERO(&readfds);

        FD_SET(STDIN_FILENO, &readfds);
        FD_SET(server_socket, &readfds);


        int max_fd = server_socket;

        if (STDIN_FILENO > max_fd)
            max_fd = STDIN_FILENO;


        select(max_fd + 1, &readfds, NULL, NULL, NULL);


        if (FD_ISSET(STDIN_FILENO, &readfds))
        {
            char line[1024];

            if (fgets(line, sizeof(line), stdin)==NULL || strcmp(line, "exit\n")==0) {
                printf("\nBye\n");
                break;
            }

            cmd(tokens(line));
        }


        if (FD_ISSET(server_socket, &readfds))
        {
            int client = acceptPlayer(players, &connected);

            if (client >= 0)
            {
                printf(
                    "Player connected (%d/%d)\n",
                    connected,
                    MAX_PLAYERS
                );
            }
        }
    }


    return 0;
}