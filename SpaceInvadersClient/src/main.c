#include "main.h"


int main(int argc, char **argv)
{
	memset(&app, 0, sizeof(App));
	
	initSDL();
	
	atexit(cleanup);

    const unsigned char *keys;
    SDL_Event event;
    int typeEvent;
    char* gameOver = FALSE;
    char* message = "0";

    while (!gameOver)
	{
		prepareScene();
		
        conexionCliente(message, argc,argv);

        if (SDL_PollEvent(&event)){
            typeEvent = event.type;
            if (typeEvent == SDL_QUIT)
                gameOver = TRUE;
            //KEYS
            else if(typeEvent == SDL_KEYDOWN){
                if (keys[SDL_SCANCODE_ESCAPE])
                    gameOver = TRUE;
                if (keys[SDL_SCANCODE_SPACE])
                    message = SHOOT;
                if (keys[SDL_SCANCODE_D] || keys[SDL_SCANCODE_RIGHT])
                    message = RIGHT;
                if (keys[SDL_SCANCODE_A] || keys[SDL_SCANCODE_LEFT])
                    message = LEFT;
                }
            else{
                    message = NONE;
            }
        }
		
        //TryFunctionXD();

		presentScene();
		
        SDL_Delay(MS);
	}

	return 0;
}
