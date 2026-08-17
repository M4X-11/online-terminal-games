#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>
#include "data.h"
#include <time.h>
#include <arpa/inet.h>
#include "snake/snakecom.h"

/* Forward declaration of client-side startMode implemented in CgameHandler.c */
int startMode(int mode);

Address addr;
Player user;
int network_socket;
int startConnection(){
    printf("connecting...");
    fflush(stdout);
    //create

    network_socket = socket(AF_INET, SOCK_STREAM, 0);

    //specify
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(addr.port);
    //server_address.sin_addr.s_addr = INADDR_ANY;
    inet_pton(AF_INET, addr.ip, &server_address.sin_addr);

    //create connect
    int connection_status = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));
    while (connection_status ==-1) {
        connection_status = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));
        usleep(100000);

    }
    printf("\nconnected to server.\n");
    recv(network_socket, &user.me, sizeof(int), 0);
    send(network_socket, user.username, sizeof(user.username), 0);
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

int sendVote(int vote){
    int r=MSG_VOTE;
    send_all(network_socket, &r, sizeof(int));
    send_all(network_socket, &vote, sizeof(int));
    return 0;
}

int sendDirection(int sock, int input){
    PacketHeader packet;
    packet.type=MSG_MOVE;
    packet.length=8;
    send_all(sock, &packet, sizeof(packet));
    send_all(sock, &input, sizeof(int));
    return 0;
}

int getData(){

    PacketHeader Cpacket;
    int action;
    recv_all(network_socket, &Cpacket, sizeof(Cpacket));
    action=Cpacket.type;
    if (action == MSG_MODE){
        recv_all(network_socket, &currentGameMode, sizeof(int));
        printf("\ncurrent game mode: %d\n", currentGameMode);
        /* Start the corresponding mode on the client */
        startMode(currentGameMode);
    }
    if (action == MSG_UPDATE_SNAKE){
        recv_all(network_socket, &packet, sizeof(packet));
        //printf("current game mode: %d\n", currentGameMode);
    }
    return 0;
}