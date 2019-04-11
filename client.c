#include <stdio.h>
//#include <sys/socket.h>
#include <stdlib.h>
//#include <netinet/in.h>
#include <string.h>
#include <SDL.h>
//#include <SDL_image.h>
#undef main

#define true 1
#define false 0

#define PORT 8080 

#define XSIZE 850
#define YSIZE 850

#define ScreenRange 50
#define MS 10

//Estructuras
typedef struct GUI_Item GUI_Item;

struct GUI_Item
{
    SDL_Surface* image;
    SDL_Rect position;
};
//Funciones
void DrawItem(GUI_Item *item, SDL_Surface *renderer);
GUI_Item CreateItem(char* name,int posX,int posY);
void TryFunctionXD(SDL_Surface *ren);

void DrawItem(GUI_Item *item,SDL_Surface *renderer){
    SDL_BlitSurface(item->image,&item->position, renderer ,NULL);
}
GUI_Item CreateItem(char* name,int posX,int posY){
    SDL_Surface* image;
    SDL_Rect position;

    if (name == 'Jugador')
        image = SDL_LoadBMP("Images/Nave.bmp");
    else if (name == 'Bala')
        image = SDL_LoadBMP("Images/Bala.bmp");
    else if (name == 'Bunker')
        image = SDL_LoadBMP("Images/Bunker.bmp");
    else if (name == 'Calamar')
        image = SDL_LoadBMP("Images/Calamar.bmp");
    else if (name == 'Pulpo')
        image = SDL_LoadBMP("Images/Pulpo.bmp");
    else if (name == 'Cangrejo')
        image = SDL_LoadBMP("Images/Cangrejo.bmp");
    else{
        image = SDL_LoadBMP("Blank.bmp");
    }
    if (image == NULL){
        printf("%s",SDL_GetError());
    }

    position.x = posX*ScreenRange;
    position.y = posY*ScreenRange;
    GUI_Item item = {
        image, position
    };
    return item;
}
void TryFunctionXD(SDL_Surface *ren){
    GUI_Item jugador;
    GUI_Item bala;
    GUI_Item bunker;
    GUI_Item calamar;
    GUI_Item pulpo;
    GUI_Item cangrejo;

    jugador = CreateItem('Jugador', 8 , 16);
    bala = CreateItem('Bala', 8 , 14);
    bunker = CreateItem('Bunker', 10 , 13);
    calamar = CreateItem('Calamar', 8 , 5);
    pulpo = CreateItem('Pulpo', 8 , 2);
    cangrejo = CreateItem('Cangrejo', 8 , 3);

    DrawItem(&jugador, &ren);
    DrawItem(&bala, &ren);
    DrawItem(&bunker, &ren);
    DrawItem(&calamar, &ren);
    DrawItem(&pulpo, &ren);
    DrawItem(&cangrejo, &ren);
}

//Main
int main()
{
    SDL_INIT_EVERYTHING;

    //Variables de Entorno
    int typeEvent;
    int gameOver;
    const unsigned char *keys;
    int message;
    SDL_Window *window;
    //SDL_Renderer *renderer;
    SDL_Event event;
    SDL_Surface *windowSurface;

    //Asignación de Variables
    window = SDL_CreateWindow("Spave Invaders", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,XSIZE,YSIZE,SDL_WINDOW_SHOWN);
    windowSurface = SDL_GetWindowSurface(window);
    //renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    gameOver = false;
    keys = SDL_GetKeyboardState(NULL);
    message = 0;

    while(!gameOver){
        //Eventos de Juego
        if (SDL_PollEvent(&event)){
            typeEvent = event.type;
            if (typeEvent == SDL_QUIT)
                gameOver=true;
            //MOUSE
            else if(typeEvent == SDL_MOUSEBUTTONDOWN){
                if (SDL_GetMouseState(NULL,NULL) && SDL_BUTTON(SDL_BUTTON_LEFT)){
                    //Haga algo
                }
            }
            //KEYS
            else if(typeEvent == SDL_KEYDOWN){
                if (keys[SDL_SCANCODE_ESCAPE])
                    gameOver = true;
                if (keys[SDL_SCANCODE_SPACE])
                    message = 1;
                if (keys[SDL_SCANCODE_D] || keys[SDL_SCANCODE_RIGHT])
                    message = 2;
                if (keys[SDL_SCANCODE_A] || keys[SDL_SCANCODE_LEFT])
                    message = 3;
            }
            else{
                message = 0;
            }
        }
        //Pantalla

        //SDL_SetRenderDrawColor(renderer,0,0,0,0);

        TryFunctionXD(windowSurface);

        SDL_UpdateWindowSurface(window);
        //SDL_RenderClear(renderer);

        //SDL_RenderPresent(renderer);
        SDL_Delay(MS);

    }
    //SDL_DestroyRenderer(renderer);
    SDL_FreeSurface(windowSurface);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
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
