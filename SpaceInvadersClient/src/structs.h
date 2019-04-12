#include "SDL.h"

typedef struct App App;
typedef struct GUI_Item GUI_Item;

struct App
{
    SDL_Renderer *renderer;
    SDL_Window *window;
};

struct GUI_Item
{
    SDL_Surface* image;
    int posX;
    int posY;
};
//Enum
enum objeto{Jugador,Bala,Bunker,Calamar,Pulpo,Cangrejo};


