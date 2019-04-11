#include "input.h"

void doInput(void)
{
	SDL_Event event;
	
    if (SDL_PollEvent(&event)){
        typeEvent = event.type;
        if (typeEvent == SDL_QUIT)
            gameOver = TRUE;
        //KEYS
        else if(typeEvent == SDL_KEYDOWN){
            if (keys[SDL_SCANCODE_ESCAPE])
                gameOver = TRUE;
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

}
