//Functions for the agent class

//Libraries
#include "agent.h"
#include "ResourceManager.h"
#include "level.h"

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

    std::vector<glm::vec2> collideTilePos;

    //Check each corner
    checkTilePos(levelData, collideTilePos, _pos.x, _pos.y);
    checkTilePos(levelData, collideTilePos, _pos.x + AGENT_WIDTH, _pos.y);
    checkTilePos(levelData, collideTilePos, _pos.x, _pos.y + AGENT_WIDTH);
    checkTilePos(levelData, collideTilePos, _pos.x + AGENT_WIDTH, _pos.y + AGENT_WIDTH);

    return;
}

//Function to check the tile position
void agent::checkTilePos(const std::vector<std::string>& levelData, std::vector<glm::vec2>& collideTilePos, float x, float y) {

    glm::vec2 cornerPos = glm::vec2(floor(x / (float)TILE_WIDTH),
                                        floor(y / (float)TILE_WIDTH));

    if (levelData[cornerPos.y][cornerPos.x] != '.') {
        collideTilePos.push_back(cornerPos + glm::vec2((float)TILE_WIDTH/2.0f));
    }

    return;
}