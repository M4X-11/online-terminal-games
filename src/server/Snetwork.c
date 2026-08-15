#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>


#include "Snetwork.h"
#include "playerState.h"
#include "Snetwork.h"
int server_socket;
int startServer(){
    //srand(time(NULL));
    //int server_socket;
    //int connected = 0;
    // Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (server_socket < 0)
    {
        perror("socket");
        return 1;
    }

    // Address
    struct sockaddr_in server_address;

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(6969);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // Bind
    if (bind(server_socket,
        (struct sockaddr*)&server_address,
        sizeof(server_address)) < 0)
    {
        perror("bind");
        return 1;
    }

    

    // Listen
    listen(server_socket, 5);
    return 0;
}

int acceptPlayer(Player *players, int *connected)
{
    int client = accept(server_socket, NULL, NULL);

    if (client < 0)
        return -1;


    if (*connected >= MAX_PLAYERS)
    {
        close(client);
        return -1;
    }


    players[*connected].socket = client;
    players[*connected].connected = 1;

    send(client, connected, sizeof(*connected), 0);
    recv(client, &players[*connected].username, sizeof(players[*connected].username), 0);
    (*connected)++;
    

    return client;
}

int disconnectPlayer(Player *players, int id){
    if (id < 0 || id >= MAX_PLAYERS)
        return -1;

    if (players[id].socket > 0)
        close(players[id].socket);

    /* Shift later players down to keep the array compact */
    for (int i = id; i < connected - 1; i++)
    {
        players[i] = players[i + 1];
    }

    /* Clear last slot */
    if (connected > 0)
    {
        players[connected - 1].socket = 0;
        players[connected - 1].connected = 0;
        memset(players[connected - 1].username, 0, sizeof(players[connected - 1].username));
        connected--;
    }

    return 0;
}

//////
int recv_all(int sock, void *buffer, size_t length)
{
    char *ptr = (char *)buffer;
    size_t total = 0;

    while (total < length)
    {
        ssize_t received = recv(sock,
                                ptr + total,
                                length - total,
                                0);

        if (received == 0)
        {
            // Peer closed the connection
            return 0;
        }

        if (received < 0)
        {
            // Socket error
            return -1;
        }

        total += received;
    }

    return (int)total;
}

int send_all(int sock, const void *buffer, size_t length)
{
    const char *ptr = (const char *)buffer;
    size_t total = 0;

    while (total < length)
    {
        ssize_t sent = send(sock,
                            ptr + total,
                            length - total,
                            0);

        if (sent <= 0)
        {
            return -1;
        }

        total += sent;
    }

    return (int)total;
}

int sendPackage(int sock, const void* buffer, size_t lenght, int action){
    switch (action)
    {
    case MSG_VOTE:
        /* code */
        break;
    
    default:
        break;
    }
    /* send action first, then payload (if any) */
    send_all(sock, &action, sizeof(int));

    if (buffer != NULL && lenght > 0)
        send_all(sock, buffer, lenght);
    return 0;
}

int sendMode(int mode){

    int action = MSG_MODE;
    for (int i = 0; i < connected; i++)
    {
        send_all(players[i].socket, &action, sizeof(int));
        send_all(players[i].socket, &mode, sizeof(int));
    
    }
    
    return 0;
}

int readPackage(int sock){
    int action;
    int vote=0;
    recv_all(sock, &action, sizeof(int));
    switch (action)
    {
    case MSG_VOTE:
        recv_all(sock, &vote, sizeof(int));
        break;
    
    default:
        break;
    }
    

    return vote;
    
}
// PAYLOADS

