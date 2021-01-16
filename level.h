//Header file for the level class

//Libraries
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "error.h"

#pragma once

class level {
    public:
        //Constructor/Destructor
        level(const std::string& fileName);
        ~level();

        void draw();

    private:
        std::vector<std::string> _levelData;
        int _numEntities;

};