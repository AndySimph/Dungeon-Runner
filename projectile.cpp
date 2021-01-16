//Functions for the projectile class

//Libraries
#include "projectile.h"

//Constructor
projectile::projectile(glm::vec2 pos, glm::vec2 dir, float speed, int lifeTime) {
    //Set default values
    _pos = pos;
    _direction = dir;
    _speed = speed;
    _lifeTime = lifeTime;
}

//Destructor
projectile::~projectile() {

}

//Draw function
void projectile::draw(spriteBatch& spriteBatch) {

    //UV values
    glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
    static GLTexture texture = ResourceManager::getText("Textures/JimmyJump_pack/PNG/Bullet.png");

    //Set color values
    Color color;
    color.r = 255;
    color.g = 255;
    color.b = 255;
    color.a = 255;

    glm::vec4 posAndSize = glm::vec4(_pos.x, _pos.y, 30, 30);

    //Draw sprites
    spriteBatch.draw(posAndSize, uv, texture.id, 0.0f, color);

    return;
}

//Function to update the projectile along the screen
bool projectile::update() {
    
    //Update the position
    _pos += _direction * _speed;

    //Decrement the lifetime
    _lifeTime--;

    //Check if there is any life left in the projectile
    if (!(_lifeTime)) {
        return true;
    }

    return false;
}