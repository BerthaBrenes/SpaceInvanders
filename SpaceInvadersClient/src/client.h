#include <winsock2.h>
#include <stdio.h>
#include "common.h"

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
//#pragma comment (lib, "Ws2_32.lib")
//#pragma comment (lib, "Mswsock.lib")
//#pragma comment (lib, "AdvApi32.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

int sock = 0, valread;
struct sockaddr_in serv_addr;
char *hello = "Hello from client";
char buffer[1024] = {0};
extern App app;

void TryFunctionXD(void);
GUI_Item CreateItem(enum objeto name,int posX,int posY);
int conexionCliente(int argc, char **argv);

