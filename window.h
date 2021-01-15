//Header file of the window class

//Libraries
#include <string>
#include <SDL2/SDL.h>
#include <GL/glew.h>

#include "error.h"

#pragma once

//Enum for window option as bit wise values
enum windowFlags {INVISIBLE = 0x1, FULLSCREEN = 0x2, BORDERLESS = 0x4};
 
class window {
    public:
        window();
        ~window();

        int create(std::string windowName, int screenWidth, int screenHeight, unsigned int currFlag);

        int getScreenWidth() { return _screenWidth; };
        int getScreenHeight() { return _screenHeight; };

        void swapBuffer();

    private:
        SDL_Window* _sdlWindow;
        int _screenWidth, _screenHeight;

};