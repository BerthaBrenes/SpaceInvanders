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
void recieveMessage(void){

}
void sendMessage(void){

}

/*
int sockets(){
    struct sockaddr_in address;
        int sock = 0, valread;
        struct sockaddr_in serv_addr;
        char *hello = "Hello from client";
        char buffer[1024] = {0};
        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
            printf("\n Socket creation error \n");
            return -1;
        }

        memset(&serv_addr, '0', sizeof(serv_addr));

        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(PORT);

        // Convert IPv4 and IPv6 addresses from text to binary form
        if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
        {
            printf("\nInvalid address/ Address not supported \n");
            return -1;
        }

        if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        {
            printf("\nConnection Failed \n");
            return -1;
        }
        send(sock , hello , strlen(hello) , 0 );
        printf("Hello message sent\n");
        valread = read( sock , buffer, 1024);
        printf("%s\n",buffer );
        return 0;
}
*/
