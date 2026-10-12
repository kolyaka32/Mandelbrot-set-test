#include <thread>
#include <mutex>
#include <math.h>

#include "main.hpp"


// Global variables
App app;

typedef double type;
// Screen position
type scale = 1.0;
type x = 0.0, y = 0.0;
type dx = 0.0, dy = 0.0;
const type maxVal = 200.0;

// Multithred system
std::mutex drawMutex;
std::thread* threads[SCREEN_HEIGHT];


void drawPoint(float _X, float _Y) {
    type zn = 0.0;
    type zi = 0.0;
    type cx = (x+_X*scale)*0.005;
    type cy = (y+_Y*scale)*0.005;
    for (int k = 0; k < 40; ++k) {
        type nzn = zn * zn - zi * zi + cx;
        type nzi = 2 * zn * zi + cy;
        zn = nzn;
        zi = nzi;

        if (abs(zn*zn+zi*zi) > maxVal) {
            drawMutex.lock();
            SDL_SetRenderDrawColor(app.renderer, 127, 127, 127, 255);
            SDL_RenderPoint(app.renderer, SCREEN_WIDTH/2 + _X, SCREEN_HEIGHT/2 + _Y);
            drawMutex.unlock();
            return;
        }
    }
}

void startCalc(float _Y) {
    for (int X=-SCREEN_WIDTH/2; X<SCREEN_WIDTH/2; ++X) {
        drawPoint(X, _Y);
    }
}

void screenshot() {
    // Creating surface from image at screen
    SDL_Surface* surface = SDL_RenderReadPixels(app.renderer, nullptr);
    // Creating name
    char name[100];
    snprintf(name, sizeof(name), "Image at %f %f.png", x, y);
    // Saving surface at file
    IMG_SavePNG(surface, name);
    SDL_DestroySurface(surface);
}

// Main function
int main(int argv, char** args) {
    // Initialasing main SDL libraries
    initSDL();

    // Initialasing objects
    /*int oldTime=SDL_GetTicks();
    dinamicText counter(40, SCREEN_WIDTH-200, 20);*/

    SDL_Event event;
    // Main game cycle
	while(app.running) {
        // Getting events
        while (SDL_PollEvent(&event) != 0) {  
            if (event.type == SDL_EVENT_QUIT) {
                // Exit from program
                app.running = false;
            }
            if (event.type == SDL_EVENT_KEY_DOWN) {
                // Resseting field and next new generation
                switch (event.key.key) {
                case SDLK_LEFT:
                case SDLK_A:
                    dx = -10;
                    break;

                case SDLK_RIGHT:
                case SDLK_D:
                    dx = 10;
                    break;

                case SDLK_UP:
                case SDLK_W:
                    dy = 10;
                    break;

                case SDLK_DOWN:
                case SDLK_S:
                    dy = -10;
                    break;

                case SDLK_PLUS:
                case SDLK_KP_PLUS:
                    scale /= 1.2;
                    break;

                case SDLK_MINUS:
                case SDLK_KP_MINUS:
                    scale *= 1.2;
                    break;

                case SDLK_E:
                    screenshot();
                    break;

                default:
                    break;
                }
            }
            if (event.type == SDL_EVENT_KEY_UP) {
                switch (event.key.key) {
                case SDLK_LEFT:
                case SDLK_RIGHT:
                case SDLK_A:
                case SDLK_D:
                    dx = 0;
                    break;

                case SDLK_UP:
                case SDLK_DOWN:
                case SDLK_W:
                case SDLK_S:
                    dy = 0;
                    break;

                default:
                    break;
                }
            }
        }
        // Camera movement
        x += dx * scale;
        y -= dy * scale;

        // Drawing
        SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 255);
        SDL_RenderClear(app.renderer);

        // Drawing need object
        for (int Y = 0; Y < SCREEN_HEIGHT; ++Y) {
            threads[Y] = new std::thread(startCalc, Y-SCREEN_HEIGHT/2);
        }
        for (int Y = 0; Y < SCREEN_HEIGHT; ++Y) {
            threads[Y]->join();
            delete threads[Y];
        }
        /*char delayText[100];
        snprintf(delayText, sizeof(delayText), "Delay: %d", SDL_GetTicks() - oldTime);
        counter.draw(delayText, {255, 255, 255});
        oldTime = SDL_GetTicks();*/
        SDL_RenderPresent(app.renderer);
	}

    // Cleaning all data
    cleanup();
	return 0;
}
