//Header file for the texture cache class

//Libraries
#include <map>
#include <string>

#include "GLTexture.h"
#include "ImgLoader.h"

#pragma once

class TextureCache {
    public:
        TextureCache();
        ~TextureCache();

        GLTexture getTexture(std::string texturePath);

    private:
        std::map<std::string, GLTexture> _textureMap;

};