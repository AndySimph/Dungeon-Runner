//Header file for sprite class

//Libraries
#include <cstddef>
#include <string>
#include <GL/glew.h>

#include "vertex.h"
#include "GLTexture.h"
#include "ResourceManager.h"

#pragma once

class sprite {
    public:
        sprite();
        ~sprite();

        void initSprite(float x, float y, float width, float height, std::string texturePath);
        void drawSprite();

    private:
        int _x;
        int _y;
        int _width;
        int _height;

        //32 bit unsigned int given using GL
        GLuint _vboID;

        GLTexture _texture;

};