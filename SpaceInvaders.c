#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <winsock2.h>

#include <stdlib.h>

#include <stdio.h>

#include <string.h>

#define DEFAULT_PORT 2007
#define DEFAULT_PROTO SOCK_STREAM
#define WIN32_LEAN_AND_MEAN

//Structs
struct Jugador
{
    int posx;
    int posy;
    int vidas;
    int vivo;
};
struct Calamar
{
    int posx;
    int posy;
    int puntos; //10
    int vivo;
};
struct Cangrejo
{
    int posx;
    int posy;
    int puntos;//20
    int vivo;
};
struct Pulpo
{
    int posx;
    int posy;
    int puntos;//40
    int vivo;
};
struct Enemigos
{
    struct Calamar calamares[22];
    struct Cangrejo cangrejos[22];
    struct Pulpo pulpos[11];
    int enemigosRestantes;
};

struct Platillo
{
    int posx;
    int posy;
    int puntos; //50 + (rand() % 51)
    int vivo;
};
struct Misil
{
    int posx;
    int posy;
    int vivo;
};

struct Balas
{
    int posx;
    int posy;
    int vivo;
};
struct EscudoSeccion
{
    int posx;
    int posy;
    int vidas;
    int vivo;
};
struct Escudo
{
    struct EscudoSeccion SuperiorIzq;
    struct EscudoSeccion SuperiorDer;
    struct EscudoSeccion InferiorIzq;
    struct EscudoSeccion InferiorDer;
};

//Funciones
void inicializar(struct Jugador *ju, struct Enemigos *e, struct Balas *b, int filas, int columnas);//posiciones iniciales
void reiniciarEnemigos(struct Enemigos *e); //posicion inicial enemigos
void colocarEscudos(struct Escudo esc[]); //posicion inicial bunkers
void colocarSeccionesEscudo(int posX , struct Escudo esc); //posicion secciones bunkers
void detectarColision(struct Jugador *ju, struct Enemigos e); //detecta si esta en un rango de colision 
void meDispararon(struct Jugador *ju, struct Misil *m); //detecta si el jugador fue impactado po una bala enemiga
void leDispare(struct Enemigos *e, struct Balas *b); //detecta si un enemigo fue impactado por una bala aleada
void debilitarEscudo(struct Escudo esc[], struct Misil *m); //detecta si un escudo fue impactado por una bala enemiga
void debilitarSeccionEscudo(struct Escudo esc, struct Misil *m);//detecta si una seccion de un escudo fue impactado por una bala enemiga
void ejecutarAccion(int accion, struct Jugador *ju, struct Balas *b);//recibe un parametro que define una accion que modifica al jugador
int serverSend(int argc, char **argv, char* message);
char* conseguirInformacion(struct Jugador ju, struct Enemigos e, struct Balas b, struct Escudo esc[]);

int main(int argc, char **argv)
{
    int fil = 17;
    int col = 17;
    int objetos = 70;
    int puntaje = 0;
    struct Jugador jugador;
    struct Enemigos enemigos;
    struct Balas bala;
    struct Escudo escudos[4];
    inicializar(&jugador, &enemigos, &bala, fil, col);
    //char * message = "Jugador,8,16/Pulpo,3,2/Pulpo,4,2";
    char * message = conseguirInformacion(jugador, enemigos, bala, escudos);
    serverSend(argc, argv, message);
    return 0;
}
char* conseguirInformacion(struct Jugador ju, struct Enemigos e, struct Balas b, struct Escudo esc[]){
    char respuesta[1000];
    int i = 0;
    int j = 0;
    if (!(ju.vivo)){
        strcpy(respuesta,"Game Over");
        return strdup(respuesta);
    }
    strcpy(respuesta,"Jugador,");
    char xAux[5];
    char yAux[5];
    sprintf(xAux, "%d", ju.posx);
    strcat(respuesta, xAux);
    strcat(respuesta, ",");
    sprintf(yAux, "%d", ju.posy);
    strcat(respuesta, yAux);
    strcat(respuesta, " ");
    if (b.vivo) {
        strcat(respuesta,"Bala,");
        sprintf(xAux, "%d", b.posx);
        strcat(respuesta, xAux);
        strcat(respuesta, ",");
        sprintf(yAux, "%d", b.posy);
        strcat(respuesta, yAux);
        strcat(respuesta, " ");
    }    
    while(i < 5)
    {
        j = 0;
        while(j < 11)
        {
            switch (i)
            {
                case 0:
                    if (e.pulpos[j].vivo) {
                        strcat(respuesta,"Pulpo,");
                        sprintf(xAux, "%d", e.pulpos[j].posx);
                        strcat(respuesta, xAux);
                        strcat(respuesta, ",");
                        sprintf(yAux, "%d", e.pulpos[j].posy);
                        strcat(respuesta, yAux);
                        strcat(respuesta, " ");
                        j++;
                    }
                    break;
                case 1:
                    if (e.cangrejos[j].vivo) {
                        strcat(respuesta,"Cangrejo,");
                        sprintf(xAux, "%d", e.cangrejos[j].posx);
                        strcat(respuesta, xAux);
                        strcat(respuesta, ",");
                        sprintf(yAux, "%d", e.cangrejos[j].posy);
                        strcat(respuesta, yAux);
                        strcat(respuesta, " ");
                        j++;
                    }
                    break;
                case 2:
                    if (e.cangrejos[j+11].vivo) {
                        strcat(respuesta,"Cangrejo,");
                        sprintf(xAux, "%d", e.cangrejos[j+11].posx);
                        strcat(respuesta, xAux);
                        strcat(respuesta, ",");
                        sprintf(yAux, "%d", e.cangrejos[j+11].posy);
                        strcat(respuesta, yAux);
                        strcat(respuesta, " ");
                        j++;

                    }
                    break;
                case 3:
                    if (e.calamares[j].vivo) {
                        strcat(respuesta,"Calamar,");
                        sprintf(xAux, "%d", e.calamares[j].posx);
                        strcat(respuesta, xAux);
                        strcat(respuesta, ",");
                        sprintf(yAux, "%d", e.calamares[j].posy);
                        strcat(respuesta, yAux);
                        strcat(respuesta, " ");
                        j++;

                    }
                    break;
                case 4:
                    if (e.calamares[j+11].vivo) {
                        strcat(respuesta,"Calamar,");
                        sprintf(xAux, "%d", e.calamares[j+11].posx);
                        strcat(respuesta, xAux);
                        strcat(respuesta, ",");
                        sprintf(yAux, "%d", e.calamares[j+11].posy);
                        strcat(respuesta, yAux);
                        strcat(respuesta, " ");
                        j++;
                    }
                    break;
                default:
                    break;
            }
        }
        i++;
    }
    int len = strlen(respuesta);
    respuesta[len] = '\0';
    printf(respuesta);
    return strdup(respuesta);
}

void inicializar(struct Jugador *ju, struct Enemigos *e, struct Balas *b, int filas, int columnas){
    ju->posx = (columnas-1)/2;
    ju->posy = filas-1;
    ju->vidas = 3;
    ju->vivo = 1;
    b->vivo = 0;
    reiniciarEnemigos(e);
}

void reiniciarEnemigos(struct Enemigos *e){
    int i;
    for(i = 2; i < 7; i++)
    {
        int j;
        for(j = 3; j < 14; j++)
        {
            switch (i)
            {
                case 2:
                    e->pulpos[j-3].posy = i;
                    e->pulpos[j-3].posx = j;
                    e->pulpos[j-3].puntos = 40;
                    e->pulpos[j-3].vivo = 1;
                    break;
                case 3:
                    e->cangrejos[j-3].posy = i;
                    e->cangrejos[j-3].posx = j;
                    e->cangrejos[j-3].puntos = 20;
                    e->cangrejos[j-3].vivo = 1;
                    break;
                case 4:
                    e->cangrejos[j+8].posy = i;
                    e->cangrejos[j+8].posx = j;
                    e->cangrejos[j+8].puntos = 20;
                    e->cangrejos[j+8].vivo = 1;
                    break;
                case 5:
                    e->calamares[j-3].posy = i;
                    e->calamares[j-3].posx = j;
                    e->calamares[j-3].puntos = 10;
                    e->calamares[j-3].vivo = 1;
                    break;
                case 6:
                    e->calamares[j+8].posy = i;
                    e->calamares[j+8].posx = j;
                    e->calamares[j+8].puntos = 10;
                    e->calamares[j+8].vivo = 1;
                    break;
                default:
                    break;
            }
        }
    }
}

void colocarEscudos(struct Escudo esc[]){
    int i;
    for(i = 0; i < 4; i++)
    {
        colocarSeccionesEscudo(3+3*i,esc[i]);
    }
}

void colocarSeccionesEscudo(int posX , struct Escudo esc){
    //posX
    esc.SuperiorDer.posx = posX;
    esc.SuperiorIzq.posx = posX+1;
    esc.InferiorDer.posx = posX;
    esc.InferiorIzq.posx = posX+1;
    //PosY
    esc.SuperiorDer.posy = 13;
    esc.SuperiorIzq.posy = 13;
    esc.InferiorDer.posy = 14;
    esc.InferiorIzq.posy = 14;
    //Vidas
    int vidas = 2;
    esc.SuperiorDer.vidas = vidas;
    esc.SuperiorIzq.vidas = vidas;
    esc.InferiorDer.vidas = vidas;
    esc.InferiorIzq.vidas = vidas;
    //Vivo   
    esc.SuperiorDer.vivo = 1;
    esc.SuperiorIzq.vivo = 1;
    esc.InferiorDer.vivo = 1;
    esc.InferiorIzq.vivo = 1;
}

void detectarColision(struct Jugador *ju, struct Enemigos e){
    int i;
    for(i = 0; i < 5; i++)
    {
        int j;
        for(j = 0; j < 11; i++)
        {
            switch (i)
            {
                case 0:
                    if ((e.pulpos[j].posy == ju->posy) && (e.pulpos[j].posx == ju->posy) && (e.pulpos[j].vivo)) {
                        ju->vivo = 0;
                    }
                    break;
                case 1:
                    if ((e.cangrejos[j].posy == ju->posy) && (e.cangrejos[j].posx == ju->posy) && (e.cangrejos[j].vivo)) {
                        ju->vivo = 0;
                    }
                    break;
                case 2:
                    if ((e.cangrejos[11+j].posy == ju->posy) && (e.cangrejos[11+j].posx == ju->posy) && (e.cangrejos[11+j].vivo)) {
                        ju->vivo = 0;
                    }
                    break;
                case 3:
                    if ((e.calamares[j].posy == ju->posy) && (e.calamares[j].posx == ju->posy) && (e.calamares[j].vivo)) {
                        ju->vivo = 0;
                    }
                    break;
                case 4:
                    if ((e.calamares[11+j].posy == ju->posy) && (e.calamares[11+j].posx == ju->posy) && (e.calamares[11+j].vivo)) {
                        ju->vivo = 0;
                    }
                    break;
                default:
                    break;
            }
        }
    }
}

void meDispararon(struct Jugador *ju, struct Misil *m){
    if ((m->posy == ju->posy) && (m->posx == ju->posy) && (m->vivo)) {
        ju->vidas--;
        m->vivo = 0;
        if (ju->vidas == 0) {
            ju->vivo = 0;
        }
        
    }
}

void leDispare(struct Enemigos *e, struct Balas *b){
    int i;
    for(i = 0; i < 5; i++)
    {
        int j;
        for(j = 0; j < 11; i++)
        {
            switch (i)
            {
                case 0:
                    if ((e->pulpos[j].posy == b->posy) && (e->pulpos[j].posx == b->posy) && (e->pulpos[j].vivo) && (b->vivo)) {
                        b->vivo = 0;
                        e->pulpos[j].vivo = 0;
                        e->enemigosRestantes--;
                    }
                    break;
                case 1:
                    if ((e->cangrejos[j].posy == b->posy) && (e->cangrejos[j].posx == b->posy) && (e->cangrejos[j].vivo) && (b->vivo)) {
                        b->vivo = 0;
                        e->cangrejos[j].vivo = 0;
                        e->enemigosRestantes--;
                    }
                    break;
                case 2:
                    if ((e->cangrejos[j+11].posy == b->posy) && (e->cangrejos[j+11].posx == b->posy) && (e->cangrejos[j+11].vivo) && (b->vivo)) {
                        b->vivo = 0;
                        e->cangrejos[j].vivo = 0;
                        e->enemigosRestantes--;
                    }
                    break;
                case 3:
                    if ((e->calamares[j].posy == b->posy) && (e->calamares[j].posx == b->posy) && (e->calamares[j].vivo) && (b->vivo)) {
                        b->vivo = 0;
                        e->calamares[j].vivo = 0;
                        e->enemigosRestantes--;
                    }
                    break;
                case 4:
                    if ((e->calamares[j+11].posy == b->posy) && (e->calamares[j+11].posx == b->posy) && (e->calamares[j+11].vivo) && (b->vivo)) {
                        b->vivo = 0;
                        e->calamares[j].vivo = 0;
                        e->enemigosRestantes--;
                    }
                    break;
                default:
                    break;
            }
        }
    }
    if (e->enemigosRestantes == 0) {
        reiniciarEnemigos(e);
    }
}

void debilitarEscudo(struct Escudo esc[], struct Misil *m){
    int i;
    for(i = 0; i < 4; i++)
    {
        debilitarSeccionEscudo(esc[i],m);
    }
    
}
void debilitarSeccionEscudo(struct Escudo esc, struct Misil *m){
    if (esc.SuperiorIzq.vivo && (esc.SuperiorIzq.posx == m->posx) && (esc.SuperiorIzq.posy == m->posy)) {
        esc.SuperiorIzq.vidas--;
        if (esc.SuperiorIzq.vidas == 0) {
            esc.SuperiorIzq.vivo = 0;
        }
    }
    else if (esc.SuperiorDer.vivo && (esc.SuperiorDer.posx == m->posx) && (esc.SuperiorDer.posy == m->posy)) {
        esc.SuperiorDer.vidas--;
        if (esc.SuperiorDer.vidas == 0) {
            esc.SuperiorDer.vivo = 0;
        }
    }
    else if (esc.SuperiorDer.vivo && (esc.SuperiorDer.posx == m->posx) && (esc.SuperiorDer.posy == m->posy)) {
        esc.SuperiorDer.vidas--;
        if (esc.SuperiorDer.vidas == 0) {
            esc.SuperiorDer.vivo = 0;
        }
    }
    else if (esc.InferiorDer.vivo && (esc.InferiorDer.posx == m->posx) && (esc.InferiorDer.posy == m->posy)) {
        esc.InferiorDer.vidas--;
        if (esc.InferiorDer.vidas == 0) {
            esc.InferiorDer.vivo = 0;
        }
    }
}

void ejecutarAccion(int accion, struct Jugador *ju, struct Balas *b){
    switch (accion)
    {
        case 0:
            break;
        case 1:
            b->vivo = 1;
            break;
        case 2:
            ju->posx++;
            break;
        case 3:
            ju->posx--;
            break;
        default:
            break;
    }
}

void Usage(char *progname)

{

    fprintf(stderr,"Usage: %s -p [protocol] -e [port_num] -i [ip_address]\n", progname);

    fprintf(stderr,"Where:\n\t- protocol is one of TCP or UDP\n");

    fprintf(stderr,"\t- port_num is the port to listen on\n");

    fprintf(stderr,"\t- ip_address is the ip address (in dotted\n");

    fprintf(stderr,"\t  decimal notation) to bind to. But it is not useful here...\n");

    fprintf(stderr,"\t- Hit Ctrl-C to terminate server program...\n");

    fprintf(stderr,"\t- The defaults are TCP, 2007 and INADDR_ANY.\n");

    WSACleanup();

    exit(1);

}

 

int serverSend(int argc, char **argv, char* message)

{

    char Buffer[1000];

    char *ip_address= NULL;

    unsigned short port=DEFAULT_PORT;

    int retval;

    int fromlen;

    int i;

    int socket_type = DEFAULT_PROTO;

    struct sockaddr_in local, from;

    WSADATA wsaData;

    SOCKET listen_socket, msgsock;

 

    /* Parse arguments, if there are arguments supplied */

    if (argc > 1)

       {

        for(i=1; i<argc; i++)

              {

                     // switches or options...

            if ((argv[i][0] == '-') || (argv[i][0] == '/'))

                     {

                            // Change to lower...if any

                           switch(tolower(argv[i][1]))

                           {

                     // if -p or /p

                    case 'p':

                        if (!stricmp(argv[i+1], "TCP"))

                            socket_type = SOCK_STREAM;

                        else if (!stricmp(argv[i+1], "UDP"))

                            socket_type = SOCK_DGRAM;

                        else

                            Usage(argv[0]);

                        i++;

                        break;

                     // if -i or /i, for server it is not so useful...

                    case 'i':

                        ip_address = argv[++i];

                        break;

                    // if -e or /e

                    case 'e':

                        port = atoi(argv[++i]);

                        break;

                     // No match...

                    default:

                        Usage(argv[0]);

                        break;

                }

            }

            else

                Usage(argv[0]);

        }

    }

 

    // Request Winsock version 2.2

    if ((retval = WSAStartup(0x202, &wsaData)) != 0)

       {

        fprintf(stderr,"Server: WSAStartup() failed with error %d\n", retval);

        WSACleanup();

        return -1;

    }

    else

       printf("Server: WSAStartup() is OK.\n");

 

    if (port == 0)

       {

        Usage(argv[0]);

    }

 

    local.sin_family = AF_INET;

    local.sin_addr.s_addr = (!ip_address) ? INADDR_ANY:inet_addr(ip_address);

 

    /* Port MUST be in Network Byte Order */

    local.sin_port = htons(port);

    // TCP socket

    listen_socket = socket(AF_INET, socket_type,0);

 

    if (listen_socket == INVALID_SOCKET){

        fprintf(stderr,"Server: socket() failed with error %d\n", WSAGetLastError());

        WSACleanup();

        return -1;

    }

    else

       printf("Server: socket() is OK.\n");

 

    // bind() associates a local address and port combination with the socket just created.

    // This is most useful when the application is a

    // server that has a well-known port that clients know about in advance.

    if (bind(listen_socket, (struct sockaddr*)&local, sizeof(local)) == SOCKET_ERROR)

       {

        fprintf(stderr,"Server: bind() failed with error %d\n", WSAGetLastError());

        WSACleanup();

        return -1;

    }

    else

              printf("Server: bind() is OK.\n");

 

     // So far, everything we did was applicable to TCP as well as UDP.

     // However, there are certain steps that do not work when the server is

     // using UDP. We cannot listen() on a UDP socket.

    if (socket_type != SOCK_DGRAM)

       {

        if (listen(listen_socket,5) == SOCKET_ERROR)

              {

            fprintf(stderr,"Server: listen() failed with error %d\n", WSAGetLastError());

            WSACleanup();

            return -1;

        }

       else

              printf("Server: listen() is OK.\n");

    }

    printf("Server: %s: I'm listening and waiting connection\non port %d, protocol %s\n", argv[0], port, (socket_type == SOCK_STREAM)?"TCP":"UDP");

 

       while(1)

       {

        fromlen =sizeof(from);

        // accept() doesn't make sense on UDP, since we do not listen()

        if (socket_type != SOCK_DGRAM)

              {

            msgsock = accept(listen_socket, (struct sockaddr*)&from, &fromlen);

            if (msgsock == INVALID_SOCKET)

           {

                fprintf(stderr,"Server: accept() error %d\n", WSAGetLastError());

                WSACleanup();

                return -1;

            }

           else

              printf("Server: accept() is OK.\n");

              printf("Server: accepted connection from %s, port %d\n", inet_ntoa(from.sin_addr), htons(from.sin_port)) ;

           

        }

        else

            msgsock = listen_socket;

 

        // In the case of SOCK_STREAM, the server can do recv() and send() on

        // the accepted socket and then close it.

        // However, for SOCK_DGRAM (UDP), the server will do recvfrom() and sendto()  in a loop.

        if (socket_type != SOCK_DGRAM)

            retval = recv(msgsock, Buffer, sizeof(Buffer), 0);

 

       else

       {

            retval = recvfrom(msgsock,Buffer, sizeof(Buffer), 0, (struct sockaddr *)&from, &fromlen);

            printf("Server: Received datagram from %s\n", inet_ntoa(from.sin_addr));

        }

           

        if (retval == SOCKET_ERROR)

              {

            fprintf(stderr,"Server: recv() failed: error %d\n", WSAGetLastError());

            closesocket(msgsock);

            continue;

        }

       else

            printf("Server: recv() is OK.\n");

 

        if (retval == 0)

              {

            printf("Server: Client closed connection.\n");

            closesocket(msgsock);

            continue;

        }

        printf("Server: Received %d bytes, data \"%s\" from client\n", retval, Buffer);

 

        printf("Server: Echoing the same data back to client...\n");

        if (socket_type != SOCK_DGRAM)

            retval = send(msgsock, message, sizeof(Buffer), 0);

        else

            retval = sendto(msgsock, message, sizeof(Buffer), 0, (struct sockaddr *)&from, fromlen);

 

              if (retval == SOCKET_ERROR)

              {

                     fprintf(stderr,"Server: send() failed: error %d\n", WSAGetLastError());

               }

              else

                     printf("Server: send() is OK.\n");

 

        if (socket_type != SOCK_DGRAM)

       {

            printf("Server: I'm waiting more connection, try running the client\n");

            printf("Server: program from the same computer or other computer...\n");

            closesocket(msgsock);

        }

        else

            printf("Server: UDP server looping back for more requests\n");

        continue;

    }

       return 0;

}