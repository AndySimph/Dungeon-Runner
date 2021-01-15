//Header file for timing classes

//Libraries
#include <SDL2/SDL.h>

#pragma once

//FPS limiter class
class fpsLimiter {
    public:
        //Constructor
        fpsLimiter();

        void setMaxFPS(float maxFPS);

        void init(float maxFPS);
        void begin();

        //Returns current FPS
        float end();

    private:
        unsigned int _startTicks;
        float _maxFPS;
        float _fps;
        float _frametime;

        void calculateFPS();

};