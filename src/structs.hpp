// Base in-game global structs
#pragma once

#include "include.hpp"

struct App{
    SDL_Renderer *renderer;
    SDL_Window *window;
};

extern App app;  // Creating main varables

// Texts variables and constants
//extern SDL_Texture *Textures[IMG_count];  // Array of all textures