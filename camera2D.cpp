//Functions for 2D Camera Class

//Libraries
#include "camera2D.h"

//Constructor
camera2D::camera2D() : _position(0.0f, 0.0f),
                        _camMatrix(1.0f),
                        _scale(1.0f),
                        _matrixUpdate(true),
                        _screenWidth(500), 
                        _screenHeight(500),
                        _orthoMatrix(1.0f) {
}
        
//Destructor
camera2D::~camera2D() {

}

//Initialize values
void camera2D::init(int screenWidth, int screenHeight) {

    _screenWidth = screenWidth;
    _screenHeight = screenHeight;
    _orthoMatrix = glm::ortho(0.0f, (float)_screenWidth, 0.0f, (float)_screenHeight);

    return;
}

//Function to update the camera
void camera2D::update() {

    //Check if there is a need for a matrix update
    if (_matrixUpdate) {

        //Set translate variable
        glm::vec3 translate(-_position.x + _screenWidth/2, -_position.y + _screenHeight/2, 0.0f);

        //Translate/ move the camera
        _camMatrix = glm::translate(_orthoMatrix, translate);

        //set scale variable
        glm::vec3 scale(_scale, _scale, 0.0f);

        //Scale the camera
        _camMatrix = glm::scale(glm::mat4(1.0f), scale) * _camMatrix;

        //Reset need to update
        _matrixUpdate = false;
    }

    return;
}

//Function to convert the coords of the screen to the world
glm::vec2 camera2D::convertScreenToWorld(glm::vec2 screenCoords) {

    //Invert y-axis
    screenCoords.y = _screenHeight - screenCoords.y;

    //Make it so that (0, 0) is the center of the camera
    screenCoords -= glm::vec2(_screenWidth/2, _screenHeight/2);

    //Scale coordinates accordingly
    screenCoords /= _scale;

    //Translate camera position
    screenCoords += _position;

    return screenCoords;
}