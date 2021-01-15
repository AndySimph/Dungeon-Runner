//Image loader functions

//Libraries
#include "ImgLoader.h"

GLTexture ImgLoader::LoadPNG(std::string filepath) {

    //Declare variables
    GLTexture texture = {};
    std::vector<unsigned char> in;
    std::vector<unsigned char> out;
    unsigned long width, height;

    //Error checking
    if (IOManager::readFileToBuffer(filepath, in) == false) {
        fatalError("Failed to load PNG file to buffer");
    }

    //Error checking
    int errorCode = decodePNG(out, width, height, &(in[0]), in.size());
    if (errorCode != 0) {
        fatalError("Decode PNG failed with error: " + std::to_string(errorCode));
    }

    //Generate openGL texture object
    glGenTextures(1, &(texture.id));

    //Bind texture and get texture image
    glBindTexture(GL_TEXTURE_2D, texture.id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out[0]));

    //Set texture parameter to wrap, magnify, and minimize
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    //Generate mipmap
    glGenerateMipmap(GL_TEXTURE_2D);

    //Unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);

    texture.width = width;
    texture.height = height;

    return texture;
}