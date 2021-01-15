//Engine.cpp, initializes system

//Libraries
#include "Engine.h"

//Function to initialize the system
int init() {

    //Initialize SDL
    SDL_Init(SDL_INIT_EVERYTHING);

    //Draw two windows so there won't be flickering, making the windows much smoother in transition
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    return 0;
}