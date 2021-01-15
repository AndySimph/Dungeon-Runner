//Image loader class jeader file

//Libraries
#include <string>
#include "GLTexture.h"
#include "IOManager.h"
#include "error.h"
#include "picopng.h"
#pragma once

class ImgLoader {
    public:
        static GLTexture LoadPNG(std::string filepath);

    private:
};