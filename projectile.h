//Header file for the projectile class

//Libraries
#include <glm/glm.hpp>

#include "spriteBatch.h"
#include "GLTexture.h"
#include "ResourceManager.h"

#pragma once

class projectile {
    public:
        //Constructor / Destructor
        projectile(glm::vec2 pos, glm::vec2 dir, float speed, int lifeTime);
        ~projectile();

        void draw(spriteBatch& spriteBatch);

        //Returns true when the projectile dies
        bool update();

    private:
        float _speed;
        glm::vec2 _direction;
        glm::vec2 _pos;
        int _lifeTime;

};