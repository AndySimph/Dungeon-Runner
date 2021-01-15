//Functions of the window class

//Libraries
#include "window.h"

//Constructor
window::window() {

}

//Destructor
window::~window() {

}

//Create the window
int window::create(std::string windowName, int screenWidth, int screenHeight, unsigned int currFlag) {

    Uint32 flags = SDL_WINDOW_OPENGL;

    if (currFlag & INVISIBLE) {
        flags |= SDL_WINDOW_HIDDEN;
    } else if (currFlag & FULLSCREEN) {
        flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
    } else if (currFlag & BORDERLESS) {
        flags |= SDL_WINDOW_BORDERLESS;
    }

    //Create window with title,x position, y position, window width, height, and open
    _sdlWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, flags);

    //Error Checking
    if (_sdlWindow == nullptr) {
        fatalError("SDL Window could not be created.");
    }

    //Create glContext
    SDL_GLContext glContext = SDL_GL_CreateContext(_sdlWindow);

    //Error Checking
    if (glContext == nullptr) {
        fatalError("SDL_GL context could not be created.");
    }

    //Set up GL error
    GLenum error = glewInit();

    //Error checking
    if (error != GLEW_OK) {
        fatalError("Could not initialize GLEW.");
    }

    //Retrieving openGL version
    //std::printf("*** OpenGL version: %s *** \n", glGetString(GL_VERSION));

    //Set background of window
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

    //V-Sync settings
    SDL_GL_SetSwapInterval(0);

    //Enable Alpha Blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return 0;
}

void window::swapBuffer() {
    //Swap the Gl windows to window
    SDL_GL_SwapWindow(_sdlWindow);

    return;
}