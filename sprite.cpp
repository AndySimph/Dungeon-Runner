//File that contains functions for the sprite class

//Libraries
#include "sprite.h"

//Constructor
sprite::sprite() : _vboID(0) {
}

//Destructor
sprite::~sprite() {
    if (_vboID) {
        glDeleteBuffers(1, &_vboID);
    }
}

//Function to initialize the sprite
void sprite::initSprite(float x, float y, float width, float height, std::string texturePath) {
    //Set default values
    _x = x;
    _y = y;
    _width = width;
    _height = height;
    _texture = ResourceManager::getText(texturePath);

    //Generate _vboID buffer it it isn't equalt to 0
    if (!(_vboID)) {
        glGenBuffers(1, &_vboID);
    }

    //Creating and setting up the data vertices
    vertex vertexData[6];

    for (int i = 0; i < 6; i++) {
        if (i == 0 || i == 5) {
            vertexData[i].setPos(x + width, y + height);
            vertexData[i].setUV(1.0f, 1.0f);
        } else if (i == 1) {
            vertexData[i].setPos(x, y + height);
            vertexData[i].setUV(0.0f, 1.0f);
        } else if (i == 4) { 
            vertexData[i].setPos(x + width, y);
            vertexData[i].setUV(1.0f, 0.0f);
        } else {
            vertexData[i].setPos(x, y);
            vertexData[i].setUV(0.0f, 0.0f);
        }
    }

    //Set the entire entity color to magenta
    for (int i = 0; i < 6; i++) {
        vertexData[i].setColor(255, 0, 255, 255);
    }

    //Set top left corner to blue
    vertexData[4].setColor(0, 0, 255, 255);

    //Set bottom right corner to green
    vertexData[4].setColor(0, 255, 0, 255);

    glBindBuffer(GL_ARRAY_BUFFER, _vboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return;
}

//Function to draw sprite
void sprite::drawSprite() {

    glBindTexture(GL_TEXTURE_2D, _texture.id);

    //Bind buffer to object
    glBindBuffer(GL_ARRAY_BUFFER, _vboID);

    //Enable the vertex attributes
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    
    //Position attribute pointer
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, pos));
    //Color attribute pointer
    glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(vertex), (void*)offsetof(vertex, color));
    //UV attribute pointer
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, uv));

    //Draw the 6 vertice on the screen
    glDrawArrays(GL_TRIANGLES, 0, 6);

    //Disable the vertex attributes
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return;
}
