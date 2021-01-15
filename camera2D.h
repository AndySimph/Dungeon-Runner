//Header file for camera 2D class

//Libraries
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#pragma once

class camera2D {
    public:
        camera2D();
        ~camera2D();

        void init(int screenWidth, int screenHeight);

        //Function to update
        void update();

        //Set functions
        void setPos(const glm::vec2& newPos) { 
            _position = newPos; 
            _matrixUpdate = true; 
            return;
        }

        void setScale(float newScale) { 
            _scale = newScale; 
            _matrixUpdate = true;
            return;
        }

        //Get functions
        glm::vec2 getPos() { return _position; }
        float getScale() { return _scale; }
        glm::mat4 getCam() { return _camMatrix; }

        glm::vec2 convertScreenToWorld(glm::vec2 screenCoords);

    private:
        int _screenWidth, _screenHeight;
        bool _matrixUpdate;
        float _scale;
        glm::vec2 _position;
        glm::mat4 _camMatrix;
        glm::mat4 _orthoMatrix;

};