//Functions for the agent class

//Libraries
#include "agent.h"
#include "ResourceManager.h"

//Constructor
agent::agent() {

}

//Destructor
agent::~agent() {

}

//Function to draw sprite batch
void agent::draw(spriteBatch& spriteBatch) {

    //Set uvRect
    const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

    //Get and set texture ID
    static int textureID = ResourceManager::getText("Textures/JimmyJump_pack/PNG/Bubble_Big.png").id;

    //Set dest rect
    glm::vec4 destRect;
    destRect.x = _pos.x;
    destRect.y = _pos.y;
    destRect.w = AGENT_WIDTH;
    destRect.z = AGENT_WIDTH;

    //Draw the sprite Batch
    spriteBatch.draw(destRect, uvRect, textureID, 0.0f, _color);

    return;
}

//Function to check collistion with the level
void agent::levelCollision(const std::vector<std::string>& levelData) {

    return;
}