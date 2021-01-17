//Header file for the agent class

//Libraries
#include <glm/glm.hpp>

#include "GLTexture.h"
#include "spriteBatch.h"

#pragma once

const float AGENT_WIDTH = 60;

class agent {
    public:
        //Constructor/Destructor
        agent();
        virtual ~agent();

        //Function to draw
        void draw(spriteBatch& spriteBatch);

        //Virtual update function
        virtual void update() = 0;

        //Getters
        glm::vec2 getPos() const { return _pos; };

    private:

    protected:
        glm::vec2 _pos;
        float _speed;
        Color _color;

};