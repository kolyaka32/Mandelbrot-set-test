
#pragma once

#include "include.hpp"


struct App {
    SDL_Renderer *renderer;
    SDL_Window *window;

    // Flag of main cycle work
    bool running;
};

extern App app;
