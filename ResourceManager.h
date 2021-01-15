//Header file for the resource manager class

//Libraries
#include <string>

#include "TextureCache.h"
#pragma once

class ResourceManager {
    public:
       static GLTexture getText(std::string texturePath);
       
       //static GLuint boundTexture;

    private:
        static TextureCache _textureCache;

};