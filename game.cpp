//File that contains functions for the game class

//Libraries
#include "game.h"

//Main game function
game::game() : _screenWidth(1024), 
                _screenHeight(768), 
                _gameState(gameState::PLAY), 
                _time(0.0f), 
                _maxFPS(60.0f) {
    _cam.init(_screenWidth, _screenHeight);
}

//Deconstructor
game::~game() {

    for (int i = 0; i < _levels.size(); i++) {
        delete _levels[i];
    }

}

//function to run the game 
void game::run() {
    initSystems();

    //Loops until game has ended
    gameLoop();

    //_levels.push_back(new level("Levels/level1.txt"));

}

//Initialize the system
void game::initSystems() {

    //Initialize the engine
    init();

    //Create window
    _window.create("Dungeon Runner", _screenWidth, _screenHeight, 0);

    //function call to initialize shaders
    initShaders();

    //Initialize fps limiter
    _fpsLimiter.init(_maxFPS);

    _levels.push_back(new level("Levels/level1.txt"));

    _currLevel = 0;

    return;
}

//Function to initialize shaders
void game::initShaders() {
    //Compile, add and link the shaders
    _colorProg.compileShaders("Shaders/colorShading.vert", "Shaders/colorShading.frag");
    _colorProg.addAttribute("vertexPos");
    _colorProg.addAttribute("vertexColor");
    _colorProg.addAttribute("vertexUV");
    _colorProg.linkShaders();
}

//Function to loop the game
void game::gameLoop() {
    
    while (_gameState != gameState::EXIT) {

        //Used for frame time measuring
        _fpsLimiter.begin();

        //Process input
        processInput();

        //Increment time
        _time += 0.01;

        //Update camera
        _cam.update();

        //Draw the board
        draw();
        
        //Find FPS
        _fps = _fpsLimiter.end();

        //Print once every 10,000 frames
        static int frameCounter = 0;
        frameCounter++;
        if (frameCounter == 10000) {
            std::cout << _fps <<std::endl;
            frameCounter = 0;
        }

    }

    return;
}

//Function to process user input
void game::processInput() {
    //Initialize event
    SDL_Event event;

    const float CAMSPEED = 5;
    const float SCALESPEED = 0.1f;

    //While loop while an event is happening within the window
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            //Event if window is quit
            case SDL_QUIT:
                _gameState = gameState::EXIT;
                break;

            //Switch case for different keyboard presses
            case SDL_KEYDOWN:
                _inputManager.keypress(event.key.keysym.sym);
                break;

            //Switch case for different keyboard releases
            case SDL_KEYUP:
                _inputManager.keyrelease(event.key.keysym.sym);
                break;

            //Mouse click
            case SDL_MOUSEBUTTONDOWN:
                _inputManager.keypress(event.button.button);
                break;

            //Mouse release
            case SDL_MOUSEBUTTONUP:
                _inputManager.keyrelease(event.button.button);
                break;

            //Record mouse motion within the window
            case SDL_MOUSEMOTION:
                _inputManager.setMouseCoord(event.motion.x, event.motion.y);
                //std::cout<<event.motion.x<<" "<<event.motion.y<< std::endl;
                break;
        }

    }
                    
    //Move the camera up if w is pressed
    if (_inputManager.iskeypressed(SDLK_w)) {
        _cam.setPos(_cam.getPos() + glm::vec2(0.0, CAMSPEED));
    }

    //Move the camera down if s is pressed
    if (_inputManager.iskeypressed(SDLK_s)) { 
        _cam.setPos(_cam.getPos() + glm::vec2(0.0, -CAMSPEED));
    }

    //Move the camera right if d is pressed
    if (_inputManager.iskeypressed(SDLK_d)) { 
        _cam.setPos(_cam.getPos() + glm::vec2(CAMSPEED, 0.0));
    }

    //Move the camera left if a is pressed
    if (_inputManager.iskeypressed(SDLK_a)) {  
        _cam.setPos(_cam.getPos() + glm::vec2(-CAMSPEED, 0.0));
    }

    //Move the camera left if a is pressed
    if (_inputManager.iskeypressed(SDLK_q)) {  
        _cam.setScale(_cam.getScale() + SCALESPEED);
    }

    //Move the camera left if a is pressed
    if (_inputManager.iskeypressed(SDLK_e)) {  
        _cam.setScale(_cam.getScale() - SCALESPEED);
    }

    //Set mouse coordinates and output it
    if (_inputManager.iskeypressed(SDL_BUTTON_LEFT)) {  
        glm::vec2 mouseCoords = _inputManager.getMouseCoord();
        mouseCoords = _cam.convertScreenToWorld(mouseCoords);
        //std::cout<<mouseCoords.x<<" "<<mouseCoords.y<< std::endl;
    }


    return;
}

//Function to draw the game
void game::draw() {

    //Clear the current buffer
    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Use the shaders
    _colorProg.enable();

    //Bind the texture
    glActiveTexture(GL_TEXTURE0);
    GLint textureLocation = _colorProg.getuniformLocation("textureSampler");
    glUniform1i(textureLocation, 0);

    //Set the time location using time
    // GLuint timeLocation = _colorProg.getuniformLocation("time");
    // glUniform1f(timeLocation, _time);

    //Set the camera matrix
    GLuint pLocation = _colorProg.getuniformLocation("p");
    glm::mat4 cameraMatrix = _cam.getCam();

    glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));


    _levels[_currLevel]->draw();

    //Disable the shaders
    _colorProg.disable();

    //Swap the Gl windows to window
    _window.swapBuffer();

    return;
}

