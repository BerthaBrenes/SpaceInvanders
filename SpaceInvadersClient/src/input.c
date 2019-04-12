#include "input.h"

void doInput(void)
{
	SDL_Event event;
	
    if (SDL_PollEvent(&event)){
        typeEvent = event.type;
        if (typeEvent == SDL_QUIT)
            app.gameOver = TRUE;
        //KEYS
        else if(typeEvent == SDL_KEYDOWN){
            if (keys[SDL_SCANCODE_ESCAPE])
                app.gameOver = TRUE;
            if (keys[SDL_SCANCODE_SPACE])
                app.message = SHOOT;
            if (keys[SDL_SCANCODE_D] || keys[SDL_SCANCODE_RIGHT])
                app.message = RIGHT;
            if (keys[SDL_SCANCODE_A] || keys[SDL_SCANCODE_LEFT])
                app.message = LEFT;
            }
        else{
                app.message = NONE;
        }
    }
}
