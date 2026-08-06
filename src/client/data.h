

#ifndef ADDRESS_H
#define ADDRESS_H

typedef struct {
    char ip[20];
    int port;
} Address;

typedef struct {
    char username[20];
    int me;
} Player;

extern Player user;

extern Address addr;
int startConnection();
#endif

