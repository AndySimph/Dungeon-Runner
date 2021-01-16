//Functions for the level class

//Libraries
#include "level.h"

//Constructor, builds and loads the level
level::level(const std::string& fileName) {

    //Open file 
    std::ifstream file;
    file.open(fileName);

    //Error checking
    if (file.fail()) {
        fatalError("Error in opening level");
    }

    //Throw away first string in temp
    std::string temp;
    file >> temp >> _numEntities;

    while (std::getline(file, temp)) {
        _levelData.push_back(temp);
    }
}

//Destructor
level::~level() {

}

void level::draw() {

}