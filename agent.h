//Header file for the agent class

//Libraries
#include <glm/glm.hpp>
#include <string>

#include "GLTexture.h"
#include "spriteBatch.h"

#pragma once

const float AGENT_WIDTH = 60;

class entity;
class player;

class agent {
    public:
        //Constructor/Destructor
        agent();
        virtual ~agent();

        //Function to draw
        void draw(spriteBatch& spriteBatch);

        //Virtual update function
        virtual void update(std::vector<std::string>& levelData,
                            std::vector<player*>& player,
                            std::vector<entity*>& entities) = 0;

        void levelCollision(const std::vector<std::string>& levelData);

        //Getters
        glm::vec2 getPos() const { return _pos; };

    private:

    protected:
        glm::vec2 _pos;
        float _speed;
        Color _color;

};