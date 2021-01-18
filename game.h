//Header file for game class

//Libraries
#include <iostream>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <GL/gl.h>

//Klyengine files
#include "sprite.h"
#include "GLTexture.h"
#include "error.h"
#include "GLSLProgram.h"
#include "window.h"
#include "Engine.h"
#include "camera2D.h"
#include "spriteBatch.h"
#include "inputManager.h"
#include "timing.h"
#include "spriteBatch.h"

//Custom files for Dungeon Runner
//#include "agent.h"
#include "player.h"
#include "entity.h"
#include "level.h"
#include "projectile.h"

#pragma once

//Enum of the game states
enum class gameState {PLAY, EXIT};

//game of class
class game{
    public:
        //Constructor and Destructor of game
        game();
        ~game();

        //Run function
        void run();

    private:
        //Variables for the window
        window _window;
        int _screenWidth;
        int _screenHeight;
        float _time;
        float _fps;
        float _maxFPS;
        
        gameState _gameState;
        GLSLProgram _colorProg;
        fpsLimiter _fpsLimiter;
        camera2D _cam;
        inputManager _inputManager;

        std::vector<level*> _levels;
        int _currLevel;

        player* _player;

        spriteBatch _agentSpriteBatch;

        std::vector<projectile> _projectiles;

        //Functions
        void initSystems();
        void initShaders();
        void gameLoop();
        void processInput();
        void draw();
        void initLevel();
        void updateAgents();

};

