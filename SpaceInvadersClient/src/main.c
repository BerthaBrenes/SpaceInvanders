#include "main.h"

int main()
{
	memset(&app, 0, sizeof(App));
	
	initSDL();
	
	atexit(cleanup);


    while (!app.gameOver)
	{
		prepareScene();
		
		doInput();
		
        TryFunctionXD();

		presentScene();
		
        SDL_Delay(MS);
	}

	return 0;
}
