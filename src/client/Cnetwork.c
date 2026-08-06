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

Address addr;
Player user;
int startConnection(){
    printf("connecting...");
    fflush(stdout);
    //create
    int network_socket;
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
    return 0;
}