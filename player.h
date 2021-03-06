//Header file for the player class

//Libraries
#include <SDL2/SDL.h>

#include "agent.h"
#include "inputManager.h"

#pragma once

class player : public agent {
    public:
        //Constructor/Destructor
        player();
        ~player();

        //Function to initalize player
        void init(float speed, glm::vec2 pos, inputManager* inputManager);

        //Update the player
        void update(std::vector<std::string>& levelData,
                    std::vector<player*>& player,
                    std::vector<entity*>& entities);

    private:
        inputManager* _inputManager;

};