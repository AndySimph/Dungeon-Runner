//Header file for the level class

//Libraries
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <glm/glm.hpp>

#include "error.h"
#include "spriteBatch.h"

#pragma once

const int TILE_WIDTH = 64;

class level {
    public:
        //Constructor/Destructor
        level(const std::string& fileName);
        ~level();

        void draw();

    private:
        std::vector<std::string> _levelData;
        int _numEntities;        
        spriteBatch _spriteBatch;
        glm::vec2 _startPlayerPos;
        std::vector<glm::vec2> _startEntityPos;

};