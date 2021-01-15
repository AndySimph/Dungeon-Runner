//Functions for timing classes

//Libraries
#include "timing.h"

//Constructor
fpsLimiter::fpsLimiter() {

}

//Function to set the target fps
void fpsLimiter::setMaxFPS(float maxFPS) {

    //Set max FPS
    _maxFPS = maxFPS;

    return;
}

//Function initializer
void fpsLimiter::init(float maxFPS) {

    //Set max FPS
    setMaxFPS(maxFPS);

    return;
}

//Function to begin the start of the FPS limiter
void fpsLimiter::begin() {

    //Get initial ticks
    _startTicks = SDL_GetTicks();

    return;
}

//Returns current FPS
float fpsLimiter::end() {

    //Calculate FPS
    calculateFPS();

    float frameTicks = SDL_GetTicks() - _startTicks;

    //Limit the max fps
    if ((1000.0f / _maxFPS) > frameTicks) {
        SDL_Delay((1000.0f / _maxFPS) - frameTicks);
    }

    return _fps;
}

void fpsLimiter::calculateFPS() {

    //Declare variables
    static const int NUM_SAMPLES = 10;
    static float frameTimes[NUM_SAMPLES];
    static int currFrame = 0;
    static float prevTicks = SDL_GetTicks();

    //Get current ticks
    float currTicks = SDL_GetTicks();

    //Set current frametime
    _frametime = currTicks - prevTicks;
    frameTimes[currFrame % NUM_SAMPLES] = _frametime;

    //Set previous ticks to current
    prevTicks = currTicks;

    //increment current frame
    int count;
    currFrame++;

    //Check if count needs to be above or below num samples
    if (currFrame < NUM_SAMPLES) {
        count = currFrame;
    } else {
        count = NUM_SAMPLES;
    }

    //Calculate average frame time
    float frameTimeAvg = 0;
    for (int i = 0; i < count; i ++) {
        frameTimeAvg += frameTimes[i];
    }
    frameTimeAvg /= count;

    //Check and adjust fps according to average frame time
    if (frameTimeAvg) {
        _fps = 1000.0f / frameTimeAvg;
    } else {
        _fps = 60.0f;
    }

    return;
}