//Header file for the IOManager class

//Libraries
#include <vector>
#include <string>
#include <fstream>
#pragma once

class IOManager {
    public:
        static bool readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer);

    private:

};