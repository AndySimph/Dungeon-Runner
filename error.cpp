//File for errors

//Libraries
#include "error.h"

//Error function
void fatalError(std::string errorStr) {
    std::cout<<errorStr<<std::endl;
    std::cout<<"Enter any key to quit"<<std::endl;
    char temp;
    std::cin>>temp;

    SDL_Quit();
    exit(69);

    return;
}