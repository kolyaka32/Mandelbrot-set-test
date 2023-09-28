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
    float x=0, y=0;
    int dx=0, dy=0;
    float scale=1;

    SDL_Surface* surface = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0, 0, 0, 0);

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
                    //x /= 1.2; y/=1.2;
                }
                if (event.key.keysym.sym == SDLK_MINUS || event.key.keysym.sym == SDLK_2 || event.key.keysym.sym == SDLK_KP_MINUS){
                    scale *= 1.2;
                    //x *= 1.2; y*=1.2;
                }
                if (event.key.keysym.sym == SDLK_e){
                    SDL_RenderReadPixels(app.renderer, NULL, surface->format->format, surface->pixels, surface->pitch);
                    //SDL_SaveBMP(surface, "file.bmp");

                    //std::string name = "file at" + std::to_string(int(x)) + "x" + std::to_string(int(y)) + ".png";
                    
                    IMG_SavePNG(surface, ("Image at " + std::to_string(int(x)) + " " + std::to_string(int(y)) + ".png").std::string::c_str());
                    
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
        
        // Drawing need object
        for(int ip=-SCREEN_WIDTH/2; ip<SCREEN_WIDTH/2; ++ip){
            for(int iq=-SCREEN_HEIGHT/2; iq<SCREEN_HEIGHT/2; ++iq){
                
                float zn = 0; float zi = 0;
                for(int k=0; k<20 / sqrt(scale); ++k){
                    float nzn = zn * zn - zi*zi + (x+ip*scale)*0.005;
                    float nzi = 2*zn * zi + (y+iq*scale)*0.005;
                    zn = nzn; zi = nzi;
                    
                    if(abs(zn*zn+zi*zi) > 1000){
                        SDL_SetRenderDrawColor(app.renderer, zn, zi, 0, 255);  // Drawing graph
                        SDL_RenderDrawPoint(app.renderer, SCREEN_WIDTH/2 + ip, SCREEN_HEIGHT/2 + iq);
                        break;
                    }
                }
            }
        }
        counter.draw("Delay: "+std::to_string((SDL_GetTicks() - oldTime)), {255, 255, 255});
        oldTime = SDL_GetTicks();
        
        SDL_RenderPresent(app.renderer);  // Blitting textures on screen
	}
    SDL_FreeSurface(surface);

    // Cleaning all data
    cleanup();
	return 0;
}