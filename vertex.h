//Header files for vertex

//Libraries
#include <GL/glew.h>
#pragma once

//Struct for positions
struct Pos {
    float x, y;
};

//Struct for color, 4 bytes for Red, Green, Blue, and Alpha(padding)
struct Color {
    GLubyte r, g, b, a;
};

//Struct for UV texture coordinates
struct UV {
    float u, v;
};

//Struct for vertex
struct vertex {
    Pos pos;
    Color color;
    UV uv;

    //Function to set position
    void setPos (float x, float y) {
        pos.x = x;
        pos.y = y;

        return;
    }

    //Function to set color
    void setColor (GLubyte r, GLubyte g, GLubyte b, GLubyte a) {
        color.r = r;
        color.g = g;
        color.a = a;
        color.b = b;

        return;
    }

    //Function to set UV
    void setUV (float u, float v) {
        uv.u = u;
        uv.v = v;

        return;
    }
};