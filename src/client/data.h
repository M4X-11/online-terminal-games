

#ifndef ADDRESS_H
#define ADDRESS_H

typedef struct {
    char ip[20];
    int port;
} Address;

extern Address addr;
int startConnection();
#endif

