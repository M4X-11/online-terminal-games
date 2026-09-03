#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>
#include "data.h"
#include <time.h>
#include <errno.h>
#include <ncurses.h>



#include "../../src/engineAPI.h"

#include <fcntl.h>
PlayerNAMES players[6];
int running = 1;

 
int main(){
    //Address addr;
    printf("Welcome to online terminal games!\n");
    char e='t';
    
    while (e=='t')
    {
        printf("Enter server IP: ");
        fflush(stdout);

        if (fgets(addr.ip, sizeof(addr.ip), stdin)==NULL || strcmp(addr.ip, "exit\n")==0) {
            printf("\nBye\n");
            break;
        }



        if (addr.ip[0]=='\n') {
            continue;
        }
        
        addr.ip[strlen(addr.ip) -1] = '\0';
        e='f';
        
    }
    int result;
    do {
        printf("Enter server port: ");
        result = scanf("%d", &addr.port);

        if (result != 1) {
            printf("Invalid input. Please enter a number.\n");

            // Clear the invalid input from the buffer
            while (getchar() != '\n');
        }
    } while (result != 1);
    
    char n='t';
    
    while (n=='t')
    {
        getchar();
        printf("Enter an username: ");
        fflush(stdout);

        if (fgets(user.username, sizeof(user.username), stdin)==NULL || strcmp(user.username, "exit\n")==0) {
            printf("\nBye\n");
            break;
        }



        if (user.username[0]=='\n') {
            continue;
        }
        
        user.username[strlen(user.username) -1] = '\0';
        n='f';
        
    }

    //network
    startConnection();
    //fcntl(network_socket, F_SETFL, O_NONBLOCK);

    displayMenu();

    while (1)
    {
        //int num;
        //printf("Vote on gamemode.\n");
        //printf("snake 0.\n");
        //printf("TTT 1.\n");
        //scanf("%d", &num);
        //sendVote(num);
        break; // exit voting loop and continue to main input loop

        ///
        fd_set readfds;

        FD_ZERO(&readfds);

        FD_SET(STDIN_FILENO, &readfds);
        FD_SET(network_socket, &readfds);

        int max_fd = network_socket;

        if (STDIN_FILENO > max_fd)
            max_fd = STDIN_FILENO;

        }
        while (running)
    {
        fd_set readfds;

        FD_ZERO(&readfds);

        FD_SET(STDIN_FILENO, &readfds);
        FD_SET(network_socket, &readfds);

        int max_fd = network_socket;

        if (STDIN_FILENO > max_fd)
            max_fd = STDIN_FILENO;


        /*
        * Wait until either:
        *
        *   1. keyboard input exists
        *   2. server data exists :3
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
            if (errno == EINTR)
                continue;

            perror("select");
            break;
        }


        //keyboard

        if (FD_ISSET(STDIN_FILENO, &readfds))
        {
            int key = getch();
            
            switch (key)
            {
                case KEY_UP:
                    sendDirection(network_socket, KEY_UP);
                    break;

                case KEY_DOWN:
                    sendDirection(network_socket, KEY_DOWN);
                    break;

                case KEY_LEFT:
                    sendDirection(network_socket, KEY_LEFT);
                    break;

                case KEY_RIGHT:
                    sendDirection(network_socket, KEY_RIGHT);
                    break;

                case ' ':
                    sendDirection(network_socket, KEY_SPACE);
                    break;

                case 'q':
                    running = 0;
                    break;
                default:
                    sendDirection(network_socket, key);
                    break;
            }
            if (current_game == NULL) {
                handleCommandInput(key);
            }
        }


        

        //gameLoop / data
            if (FD_ISSET(network_socket, &readfds))
        {
            //printf("Data from server\n");
            getData();

            /*
            * Update local game state.
            */
            gameLoop();
        }
    }
    return 0;
}