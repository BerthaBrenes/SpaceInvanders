#include "common.h"
// Client program example
#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define DEFAULT_PORT 2007

// TCP socket type

#define DEFAULT_PROTO SOCK_STREAM

#define DEFAULT_BUFLEN 512

int sock = 0, valread;
struct sockaddr_in serv_addr;
char *hello = "Hello from client";
char buffer[1024] = {0};
extern App app;

void TryFunctionXD(void);
void DrawServerInfo(char * message);
GUI_Item CreateItem(enum objeto name,int posX,int posY);
int conexionCliente(char *message, int argc, char **argv);

