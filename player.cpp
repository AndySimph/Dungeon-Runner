//Functions for the player class

//Libraries
#include "player.h"

//Constructor
player::player() {

}

//Destructor
player::~player() {

}

//Function to initialize the player
void player::init(float speed, glm::vec2 pos, inputManager* inputManager) {

    //Set player values
    _speed = speed;
    _pos = pos;
    _color.r = 0;
    _color.g = 0;
    _color.b = 128;
    _color.a = 255;
    _inputManager = inputManager;

    return;
}

//Function to update the player
void player::update(std::vector<std::string>& levelData,
                    std::vector<player*>& player,
                    std::vector<entity*>& entities) {

    //Move the player up or down
    if (_inputManager->iskeypressed(SDLK_w)) {
        _pos.y += _speed;
    } else if (_inputManager->iskeypressed(SDLK_s)) {
        _pos.y -= _speed;
    }

    //Move the player left or right
    if (_inputManager->iskeypressed(SDLK_a)) {
        _pos.x -= _speed;
    } else if (_inputManager->iskeypressed(SDLK_d)) {
        _pos.x += _speed;
    }

    return;
}