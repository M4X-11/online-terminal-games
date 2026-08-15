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
#include <fcntl.h>
#include <errno.h>
#include <sys/time.h>

Address addr;
Player user;
int network_socket;

static int set_nonblocking(int fd)
{
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags == -1)
        return -1;
    return fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}

static int nonblocking_connect(int sock, const struct sockaddr *addr, socklen_t alen, int timeout_sec)
{
    int ret = connect(sock, addr, alen);
    if (ret == 0)
        return 0;

    if (errno != EINPROGRESS)
        return -1;

    fd_set wf;
    FD_ZERO(&wf);
    FD_SET(sock, &wf);
    struct timeval tv;
    tv.tv_sec = timeout_sec;
    tv.tv_usec = 0;

    ret = select(sock + 1, NULL, &wf, NULL, &tv);
    if (ret <= 0)
        return -1; /* timeout or error */

    int err = 0;
    socklen_t len = sizeof(err);
    if (getsockopt(sock, SOL_SOCKET, SO_ERROR, &err, &len) < 0)
        return -1;

    if (err != 0)
    {
        errno = err;
        return -1;
    }

    return 0;
}
int startConnection(){
    printf("connecting...");
    fflush(stdout);
    //create

    network_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (network_socket < 0) {
        perror("socket");
        return -1;
    }

    if (set_nonblocking(network_socket) < 0) {
        perror("set_nonblocking");
        close(network_socket);
        return -1;
    }

    /* specify */
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(addr.port);
    inet_pton(AF_INET, addr.ip, &server_address.sin_addr);

    /* non-blocking connect with 5s timeout */
    if (nonblocking_connect(network_socket, (struct sockaddr *)&server_address, sizeof(server_address), 5) < 0) {
        perror("connect");
        close(network_socket);
        return -1;
    }

    printf("\nconnected to server.\n");

    /* read assigned id (blocking-aware) */
    ssize_t r = recv(network_socket, &user.me, sizeof(int), 0);
    while (r < 0 && (errno == EAGAIN || errno == EWOULDBLOCK || errno == EINTR)) {
        if (errno == EINTR) { r = recv(network_socket, &user.me, sizeof(int), 0); continue; }

        fd_set rf;
        FD_ZERO(&rf);
        FD_SET(network_socket, &rf);
        if (select(network_socket + 1, &rf, NULL, NULL, NULL) <= 0) {
            perror("select recv");
            close(network_socket);
            return -1;
        }

        r = recv(network_socket, &user.me, sizeof(int), 0);
    }

    if (r <= 0) {
        perror("recv id");
        close(network_socket);
        return -1;
    }

    /* send username (may be partial if socket busy; keep simple and use send normally) */
    ssize_t s = send(network_socket, user.username, sizeof(user.username), 0);
    if (s <= 0) {
        perror("send username");
        /* not fatal here, keep connection open */
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

int sendVote(int vote){
    int r=MSG_VOTE;
    send_all(network_socket, &r, sizeof(int));
    send_all(network_socket, &vote, sizeof(int));
    return 0;
}

int getData(){

    int action;
    recv_all(network_socket, &action, sizeof(int));
    if (action == MSG_MODE){
        recv_all(network_socket, &currentGameMode, sizeof(int));
        printf("current game mode: %d\n", currentGameMode);
    }
    return 0;
}