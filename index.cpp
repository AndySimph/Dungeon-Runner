//Programmer: Andy Simphaly
//Driver file

//Compile command
//g++ *.cpp -lSDL2 -lGLEW -lGL
//g++ *.cpp -lSDL2 -lGLEW -lGL -lglut

//Libraries
#include "game.h"

int main (int argc, char** argv) {
    //Declare and run game
    game mainGame;
    mainGame.run();

    return 0;
}