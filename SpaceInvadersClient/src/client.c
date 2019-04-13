#include "client.h"

GUI_Item CreateItem(enum objeto name,int posX,int posY){
    GUI_Item item;
    //memset(&item, 0, sizeof(GUI_Item));

    item.posX = posX;
    item.posY = posY;

    if (name == Jugador)
        item.image = loadTexture("Images/Nave.bmp");
    else if (name == Bala)
        item.image = loadTexture("Images/Bala.bmp");
    else if (name == Bunker)
        item.image = loadTexture("Images/Bunker.bmp");
    else if (name == Calamar)
        item.image = loadTexture("Images/Calamar.bmp");
    else if (name == Pulpo)
        item.image = loadTexture("Images/Pulpo.bmp");
    else if (name == Cangrejo)
        item.image = loadTexture("Images/Cangrejo.bmp");
    else{
        item.image = loadTexture("Images/Blank.bmp");
    }
    if (item.image == NULL){
        printf("%s",SDL_GetError());
    }
    return item;
}
void TryFunctionXD(){
    GUI_Item jugador;
    GUI_Item bala;
    GUI_Item bunker;
    GUI_Item calamar;
    GUI_Item pulpo;
    GUI_Item cangrejo;

    jugador = CreateItem(Jugador, 8 , 16);
    bala = CreateItem(Bala, 8 , 14);
    bunker = CreateItem(Bunker, 10 , 13);
    calamar = CreateItem(Calamar, 8 , 5);
    pulpo = CreateItem(Pulpo, 8 , 2);
    cangrejo = CreateItem(Cangrejo, 8 , 3);

    blit(jugador.image,jugador.posX,jugador.posY);
    blit(bala.image,bala.posX,bala.posY);
    blit(bunker.image,bunker.posX,bunker.posY);
    blit(calamar.image,calamar.posX,calamar.posY);
    blit(pulpo.image,pulpo.posX,pulpo.posY);
    blit(cangrejo.image,cangrejo.posX,cangrejo.posY);
}
void Usage(char *progname){
    fprintf(stderr,"Usage: %s -p [protocol] -n [server name/IP] -e [port_num] -l [iterations]\n", progname);
    fprintf(stderr,"Where:\n\tprotocol is one of TCP or UDP\n");
    fprintf(stderr,"\t- server is the IP address or name of server\n");
    fprintf(stderr,"\t- port_num is the port to listen on\n");
    fprintf(stderr,"\t- iterations is the number of loops to execute.\n");
    fprintf(stderr,"\t- (-l by itself makes client run in an infinite loop,\n");
    fprintf(stderr,"\t- Hit Ctrl-C to terminate it)\n");
    fprintf(stderr,"\t- The defaults are TCP , localhost and 2007\n");
    WSACleanup();

    exit(1);
}
void DrawServerInfo(char * message){
    char delim1[] =" ";
    char *ptr = strtok(message, delim1);
    int i = 0;
    char * arr[55];
    while(ptr != NULL){
        arr[i] = ptr;
        i++;
        ptr = strtok(NULL, delim1);
    }
    foreach(char ** ele , arr){
        char delim2[] =",";
        char *ptr2 = strtok(*ele, delim2);
        enum objeto name;
        int posX;
        int posY;
        if (0 == strncmp(ptr2,"Jugador",3))
            name = Jugador;
        else if (0 == strncmp(ptr2,"Bala",3))
            name = Bala;
        else if (0 == strncmp(ptr2,"Escudo",3))
            name = Bunker;
        else if (0 == strncmp(ptr2,"Calamar",3))
            name = Calamar;
        else if (0 == strncmp(ptr2,"Pulpo",3))
            name = Pulpo;
        else if (0 == strncmp(ptr2,"Cangrejo",3))
            name = Cangrejo;
        else{
            name = Bala;
            printf ("Error");
        }
        ptr2 = strtok(NULL, delim2);
        posX = atoi(ptr2);
        printf(ptr);
        ptr2 = strtok(NULL, delim2);
        posY = atoi(ptr2);
        printf(ptr);
        //Dibujar en Pantalla
        GUI_Item objeto = CreateItem(name, posX , posY);
        blit(objeto.image,objeto.posX,objeto.posY);

    }
}


int conexionCliente(char* message, int argc, char **argv)
{

        char Buffer[1000];

        // default to localhost

        char *server_name= "192.168.1.22";

        unsigned short port = DEFAULT_PORT;

        int retval, loopflag = 0;

        int i, loopcount, maxloop=-1;

        unsigned int addr;

        int socket_type = DEFAULT_PROTO;

        struct sockaddr_in server;

        struct hostent *hp;

        WSADATA wsaData;

        SOCKET  conn_socket;



        if (argc >1)

           {

            for(i=1; i<argc; i++)

            {

                if ((argv[i][0] == '-') || (argv[i][0] == '/'))

               {

                    switch(tolower(argv[i][1]))

                     {

                        case 'p':

                            if (!stricmp(argv[i+1], "TCP"))

                                socket_type = SOCK_STREAM;

                            else if (!stricmp(argv[i+1], "UDP"))

                                socket_type = SOCK_DGRAM;

                            else

                                Usage(argv[0]);

                            i++;

                            break;

                        case 'n':

                            server_name = argv[++i];

                            break;

                        case 'e':

                            port = atoi(argv[++i]);

                            break;

                        case 'l':

                            loopflag =1;

                            if (argv[i+1]) {

                                if (argv[i+1][0] != '-')

                                    maxloop = atoi(argv[i+1]);

                            }

                            else

                                maxloop = -1;

                            i++;

                            break;

                        default:

                            Usage(argv[0]);

                            break;

                    }

                }

                else

                    Usage(argv[0]);

            }

        }



        if ((retval = WSAStartup(0x202, &wsaData)) != 0)

        {

           fprintf(stderr,"Client: WSAStartup() failed with error %d\n", retval);

            WSACleanup();

            return -1;

        }

        else

           printf("Client: WSAStartup() is OK.\n");



        if (port == 0)

        {

            Usage(argv[0]);

        }

        // Attempt to detect if we should call gethostbyname() or gethostbyaddr()

        if (isalpha(server_name[0]))

        {   // server address is a name

            hp = gethostbyname(server_name);

        }

        else

        { // Convert nnn.nnn address to a usable one

            addr = inet_addr(server_name);

            hp = gethostbyaddr((char *)&addr, 4, AF_INET);

        }

        if (hp == NULL )

        {

            fprintf(stderr,"Client: Cannot resolve address \"%s\": Error %d\n", server_name, WSAGetLastError());

            WSACleanup();

            exit(1);

        }

        else

           printf("Client: gethostbyaddr() is OK.\n");

        // Copy the resolved information into the sockaddr_in structure

        memset(&server, 0, sizeof(server));

        memcpy(&(server.sin_addr), hp->h_addr, hp->h_length);

        server.sin_family = hp->h_addrtype;

        server.sin_port = htons(port);



        conn_socket = socket(AF_INET, socket_type, 0); /* Open a socket */

        if (conn_socket <0 )

        {

            fprintf(stderr,"Client: Error Opening socket: Error %d\n", WSAGetLastError());

            WSACleanup();

            return -1;

        }

        else

           printf("Client: socket() is OK.\n");



        // Notice that nothing in this code is specific to whether we

        // are using UDP or TCP.

        // We achieve this by using a simple trick.

        //    When connect() is called on a datagram socket, it does not

        //    actually establish the connection as a stream (TCP) socket

        //    would. Instead, TCP/IP establishes the remote half of the

        //    (LocalIPAddress, LocalPort, RemoteIP, RemotePort) mapping.

        //    This enables us to use send() and recv() on datagram sockets,

        //    instead of recvfrom() and sendto()

        printf("Client: Client connecting to: %s.\n", hp->h_name);

        if (connect(conn_socket, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR)

        {

            fprintf(stderr,"Client: connect() failed: %d\n", WSAGetLastError());

            WSACleanup();

            return -1;

        }

        else

           printf("Client: connect() is OK.\n");



        // Test sending some string

        loopcount = 0;

        while(1)

        {
            wsprintf(Buffer, message, loopcount++);

            retval = send(conn_socket, Buffer, sizeof(Buffer), 0);

            if (retval == SOCKET_ERROR)

            {

                fprintf(stderr,"Client: send() failed: error %d.\n", WSAGetLastError());

                WSACleanup();

                return -1;

            }

            else

              printf("Client: send() is OK.\n");

            printf("Client: Sent data \"%s\"\n", Buffer);



                  retval = recv(conn_socket, Buffer, sizeof(Buffer), 0);

            if (retval == SOCKET_ERROR)

           {

                fprintf(stderr,"Client: recv() failed: error %d.\n", WSAGetLastError());

                closesocket(conn_socket);

                WSACleanup();

                return -1;

            }

            else

                printf("Client: recv() is OK.\n");



            // We are not likely to see this with UDP, since there is no

            // 'connection' established.

            if (retval == 0)

           {

                printf("Client: Server closed connection.\n");

                closesocket(conn_socket);

                WSACleanup();

                return -1;

            }




            printf("Client: Received %d bytes, data \"%s\" from server.\n", retval, Buffer);
            //Aqui va mi codigo
            DrawServerInfo(Buffer);


            if (!loopflag)

           {

                printf("Client: Terminating connection...\n");

                break;

            }

            else

           {

                if ((loopcount >= maxloop) && (maxloop >0))

                break;

            }

        }

        closesocket(conn_socket);

        WSACleanup();



    return 0;
}
