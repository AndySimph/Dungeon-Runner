//Functions for input manager class

//Libraries
#include "inputManager.h"

//Constructor
inputManager::inputManager() : _mouseCoords(0.0f, 0.0f) {

}

//Destructor
inputManager::~inputManager() {

}

//Function to interpret when a key is pressed
void inputManager::keypress(unsigned int keyID) {

    //Check if the keyID is in the map, if not create it and set it to true
    _keymap[keyID] = true;

    return;
}

//Function to interpret when a key is released
void inputManager::keyrelease(unsigned int keyID) {

    //Check if the keyID is in the map, if not create it and set it to false
    _keymap[keyID] = false;

    return;
}

//Function to check whether a key is pressed
bool inputManager::iskeypressed(unsigned int keyID) {

    //Set it to the value where keyID is
    auto it = _keymap.find(keyID);

    //Check if the ID is found
    if (it != _keymap.end()) {
        return it->second;
    } else {
        return false;
    }

}

//Function to set mouse coordinates
void inputManager::setMouseCoord(float x, float y) {

    //Set mouse coords
    _mouseCoords.x = x;
    _mouseCoords.y = y;

    return;
}