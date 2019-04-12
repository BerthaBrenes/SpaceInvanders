#include "main.h"

int main(int argc, char **argv)
{
	memset(&app, 0, sizeof(App));
	
	initSDL();
	
	atexit(cleanup);


    while (!app.gameOver)
	{
		prepareScene();
		
        conexionCliente(argc,argv);

		doInput();
		
        TryFunctionXD();

		presentScene();
		
        SDL_Delay(MS);
	}

	return 0;
}
