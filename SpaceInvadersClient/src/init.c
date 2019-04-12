#include "init.h"

void initSDL(void)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}

    app.window = SDL_CreateWindow("Space Invader", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	
	if (!app.window)
	{
		printf("Failed to open %d x %d window: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());
		exit(1);
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    app.renderer = SDL_CreateRenderer(app.window, -1, SDL_RENDERER_ACCELERATED);
	
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

    app.gameOver = FALSE;

    app.message = NONE;
}

void cleanup(void)
{
	SDL_DestroyRenderer(app.renderer);
	
	SDL_DestroyWindow(app.window);
	
	SDL_Quit();
}
