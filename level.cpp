//Functions for the level class

//Libraries
#include "level.h"
#include "ResourceManager.h"

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

    _spriteBatch.init();
    _spriteBatch.begin();

    glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
    Color color;
    color.r = 255;
    color.g = 255;
    color.b = 255;
    color.a = 255;

    //Loop to go though the x and y coords of the file
    for (int i = 0; i < _levelData.size(); i++) {
        for (int j = 0; j < _levelData[i].size(); j++) {

            //Set the tile
            char tile = _levelData[i][j];

            //Get dest Rect
            glm::vec4 destRect(j * TILE_WIDTH, i * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH);

            //Process the tile
            switch (tile)
            {
            //Red brick tile
            case 'R':

                _spriteBatch.draw(destRect, uvRect, ResourceManager::getText("Textures/JimmyJump_pack/PNG/red_bricks.png").id, 0.0f, color);

                break;
            case '@':

                _startPlayerPos.x = j * TILE_WIDTH;
                _startPlayerPos.y = i * TILE_WIDTH;
            
                break;
            case 'Z':

                _startEntityPos.emplace_back(j * TILE_WIDTH, i * TILE_WIDTH);

                break;
            case '.':

                break;
            default:
            
                break;

            }

        }
    }

    _spriteBatch.end();
}

//Destructor
level::~level() {

}

void level::draw() {

    _spriteBatch.renderBatch();

    return;
}