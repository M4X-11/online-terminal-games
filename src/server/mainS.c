#include <stdio.h>
#include <unistd.h>
#include <sys/select.h>
#include <string.h>
#include <stdlib.h>

#include "Snetwork.h"
#include "commands.h"
#include "playerState.h"
#include "gameHandler.h"

//gamlist
#include "../../games/GameHeader.h"

#include "../../src/engineAPI.h"

int desired_ms;


Player players[MAX_PLAYERS] = {0};
int connected = 0;




int port;


int main()
{
    desired_ms=100000;
    printf("Welcome to online terminal games\n\n");
    int result;
    do {
        printf("Enter server port: ");
        result = scanf("%d", &port);

        if (result != 1) {
            printf("Invalid input. Please enter a number.\n");

            // Clear the invalid input from the buffer
            while (getchar() != '\n');
        }
    } while (result != 1);
    

    printf("Started server!\n\n");

    startServer(port);

    printf("OTG$ ");
    fflush(stdout);

    

    while (1)
    {
        fd_set readfds;

        FD_ZERO(&readfds);


        
        //terminal
        FD_SET(STDIN_FILENO, &readfds);


        //server socket
        FD_SET(server_socket, &readfds);

        int max_fd = server_socket;

        if (STDIN_FILENO > max_fd)
            max_fd = STDIN_FILENO;


        //all player sockets
        for (int i = 0; i < MAX_PLAYERS; i++)
        {
            if (players[i].socket > 0)
            {
                FD_SET(players[i].socket, &readfds);

                if (players[i].socket > max_fd)
                    max_fd = players[i].socket;
            }
        }


        // game tick rate
        struct timeval timeout;
        timeout.tv_sec = 0;
        timeout.tv_usec = desired_ms;; // 50 ms// 100 ms


        

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


        // terminal input

        if (FD_ISSET(STDIN_FILENO, &readfds))
        {
            char line[1024];

            if (fgets(line, sizeof(line), stdin) == NULL)
            {
                printf("\nBye\n");
                break;
            }


            

            line[strcspn(line, "\n")] = '\0';


            

            if (strcmp(line, "exit") == 0)
            {
                printf("\nBye\n");
                break;
            }


            

            if (line[0] == '\0')
            {
                if (app_state == STATE_IN_GAME && current_game != NULL)
            {
                printf("(%s)-OTG$ ", current_game->name);

                //printf("Game loop running\n");
                fflush(stdout);
            }else
            {
            printf("OTG$ ");
            fflush(stdout);}
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


            if (app_state == STATE_IN_GAME && current_game != NULL)
            {
                printf("(%s)-OTG$ ", current_game->name);

                //printf("Game loop running\n");
                fflush(stdout);
            }else
            {
            printf("OTG$ ");
            fflush(stdout);}
        }


        // new connections

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

                if (app_state == STATE_IN_GAME && current_game != NULL)
            {
                printf("(%s)-OTG$ ", current_game->name);

                //printf("Game loop running\n");
                fflush(stdout);
            }else
            {
            printf("OTG$ ");
            fflush(stdout);}
            }
        }


        // player data
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
                    players[i].socket,
                    i
                );
                //printf("got data from player %d\n", i);
                fflush(stdout);
            }
        }


        // game loop

        if (app_state == STATE_IN_GAME && current_game != NULL)
        {
            gameLoop();

        }
    }


    return 0;
}

