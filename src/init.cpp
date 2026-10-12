
#include "init.hpp"


void initSDL() {
    // Initialising SDL libarary
    SDL_Init(SDL_INIT_VIDEO);

	app.window = SDL_CreateWindow(WINDOWNAME, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	app.renderer = SDL_CreateRenderer(app.window, nullptr);
    app.running = true;

    TTF_Init();  // Initialasing fonts library
    //Mix_Init(MIX_INIT_OGG | MIX_INIT_FLAC);
    //Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 );
}

void cleanup()
{
    // Closing all outside libraries
	SDL_DestroyRenderer(app.renderer);
	SDL_DestroyWindow(app.window);
	
    //Mix_CloseAudio();
    //Mix_Quit();
    TTF_Quit();
	SDL_Quit();
}
