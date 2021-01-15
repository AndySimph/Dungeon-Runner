//Function file for the IOManager class

//Libraries
#include "IOManager.h"

bool IOManager::readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer) {

    //Set file stream and error check
    std::ifstream file(filePath, std::ios::binary);
    if (file.fail()) {
        perror(filePath.c_str());
        return false;
    }

    //Seek to the end
    file.seekg(0, std::ios::end);

    //Get file size
    unsigned int fileSize = (unsigned int)file.tellg();
    file.seekg(0, std::ios::beg);

    //Ignore file header bytes
    fileSize -= (unsigned int)file.tellg();

    //Read in file
    buffer.resize(fileSize);
    file.read((char *)&(buffer[0]), fileSize);

    //Close file
    file.close();

    return true;
}