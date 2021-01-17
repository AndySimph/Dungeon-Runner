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

        //Draw function
        void draw();

        //Getters
        glm::vec2 getStartPlayerPos() const { return _startPlayerPos; };
        const std::vector<glm::vec2> getStartEntityPos() const { return _startEntityPos; };

    private:
        std::vector<std::string> _levelData;
        int _numEntities;        
        spriteBatch _spriteBatch;
        glm::vec2 _startPlayerPos;
        std::vector<glm::vec2> _startEntityPos;

};