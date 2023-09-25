#include "include.hpp"
#include "define.hpp"
#include "structs.hpp"

#include "init.hpp"
#include "perlin.hpp"
#include "baseHud.hpp"

#include "main.hpp"


// Global variables of other
App app;

// Flags of running
bool running = true;  // Flag of main cycle work


//const siv::PerlinNoise perlin;

// Main function
int main(int argv, char** args){
    initSDL();  // Initialasing of main SDL library
    

    SDL_Event event;

    //const siv::PerlinNoise::seed_type seed = Perseed;
	//const siv::PerlinNoise perlin{ seed };

    // Initialasing objects

    int oldTime=SDL_GetTicks();
    dinamicText counter(40, SCREEN_WIDTH-200, 20);
    int x=0, y=0, dx=0, dy=0;
    float scale=1;
    // Main game cycle
	while(running)
	{
        // Getting events
        while( SDL_PollEvent(&event) != 0 ){  
            if (event.type == SDL_QUIT){
                running = false;  // Exit from program
            }
            if (event.type == SDL_KEYDOWN) {
                // Resseting field and next new generation
                if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_a){
                    dx = -10;
                }
                if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d){
                    dx = 10;
                }
                if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_w){
                    dy = 10;
                }
                if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s){
                    dy = -10;
                }
                if (event.key.keysym.sym == SDLK_PLUS || event.key.keysym.sym == SDLK_1 || event.key.keysym.sym == SDLK_KP_PLUS){
                    scale /= 1.2;
                }
                if (event.key.keysym.sym == SDLK_MINUS || event.key.keysym.sym == SDLK_2 || event.key.keysym.sym == SDLK_KP_MINUS){
                    scale *= 1.2;
                }
            }
            if (event.type == SDL_KEYUP) {
                if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_RIGHT 
                || event.key.keysym.sym == SDLK_a || event.key.keysym.sym == SDLK_d) {
                    dx = 0;
                }
                if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_w || 
                event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s){
                    dy = 0;
                }
            }
        }

        // Updating on screen objects
        x+=dx*scale; y-=dy*scale;
        
        // Drawing objects at screen
        SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 255);  // Drawing surrounding
        SDL_RenderClear(app.renderer);

        const float pmin = -2.5, pmax = 1.5, qmin = -2, qmax = 2;
        
        
        // Drawing need object
        for(int ip=-SCREEN_WIDTH/2; ip<SCREEN_WIDTH/2; ++ip){
            for(int iq=-SCREEN_HEIGHT/2; iq<SCREEN_HEIGHT/2; ++iq){
                
                float zn = 0; float zi = 0;
                for(int k=0; k<300; ++k){
                    float nzn = zn * zn - zi*zi + (ip+x)*0.005*scale;
                    float nzi = 2*zn * zi + (iq+y)*0.005*scale;
                    zn = nzn; zi = nzi;
                    
                    if(abs(zn*zn+zi*zi) > 10000){
                        SDL_SetRenderDrawColor(app.renderer, zn, zi, zn, 255);  // Drawing graph
                        SDL_RenderDrawPoint(app.renderer, SCREEN_WIDTH/2 + ip, SCREEN_HEIGHT/2 + iq);
                        break;
                    }
                }
            }
        }
        counter.draw("FPS: "+std::to_string(1000/(SDL_GetTicks() - oldTime)), {0, 0, 0});
        oldTime = SDL_GetTicks();

        SDL_RenderPresent(app.renderer);  // Blitting textures on screen
	}

    // Cleaning all data
    cleanup();
	return 0;
}