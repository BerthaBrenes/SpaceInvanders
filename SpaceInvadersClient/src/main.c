#include "main.h"

int main()
{
    gameOver = FALSE;
	memset(&app, 0, sizeof(App));
	
	initSDL();
	
	atexit(cleanup);


    while (!gameOver)
	{
		prepareScene();
		
		doInput();
		
        TryFunctionXD();

		presentScene();
		
        SDL_Delay(MS);
	}

	return 0;
}
