//Header file for the entity class

//Libraries
#include "agent.h"

#pragma once

class entity : public agent {
    public:
        //Constructor/Destructor
        entity();
        ~entity();

        //Virtual update
        virtual void update();

    private:

};