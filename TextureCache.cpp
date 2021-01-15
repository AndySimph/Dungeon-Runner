//Functions of the texture cache class

//Libraries
#include "TextureCache.h"

//Constructor
TextureCache::TextureCache() {

}
        
//Destructor
TextureCache::~TextureCache() {

}

//Function to get the texture
GLTexture TextureCache::getTexture(std::string texturePath) {

    //Look up texture to see if its in the map
    //Auto takes place of std::map<std::string, GLTexture>::iterator
    auto mit = _textureMap.find(texturePath);

    //Check if texture is in the map
    if (mit == _textureMap.end()) {
        //Load the texture
        GLTexture newText = ImgLoader::LoadPNG(texturePath);

        //Insert texture into the map
        _textureMap.insert(make_pair(texturePath, newText));

        return newText;
    }

    return mit->second;
}