//Header file for sprite batch class

//Libraries
#include <vector>
#include <algorithm>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "vertex.h"

#pragma once

//Glyph sort type
enum class glyphSortType {NONE, FRONT_TO_BACK, BACK_TO_FRONT, TEXTURE};

//Struct for glyph
struct glyph {

    //Values
    GLuint texture;
    float depth;
    
    //Vertex locations
    vertex topLeft;
    vertex botLeft;
    vertex topRight;
    vertex botRight;

};

//Render batch class
class RenderBatch {
    public:
        //Constructor
        RenderBatch(GLuint Offset, GLuint NumVertices, GLuint Texture) :
                offset(Offset), 
                numVertices(NumVertices), 
                texture(Texture) {}

        GLuint offset;
        GLuint numVertices;
        GLuint texture;

};

//Sprite Batch class
class spriteBatch {
    public:
        //Constructor / Destructor
        spriteBatch();
        ~spriteBatch();

        //Initialize the class
        void init();

        //Set up class for drawing/ post processing of batch
        void begin(glyphSortType sortType = glyphSortType::TEXTURE);
        void end();

        //Draw sprites to batch
        void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color& color);

        //Render batch to screen
        void renderBatch();

    private:
        GLuint _vbo;
        GLuint _vao;

        std::vector<glyph *> _glyphs;
        glyphSortType _sortType;
        std::vector<RenderBatch> _renderbatches;

        //Functions
        void createVertexArray();
        void sortGlyphs();
        void createRenderBatches();

        static bool compareFrontToBack(glyph* a, glyph* b);
        static bool compareBacktoFront(glyph* a, glyph* b);
        static bool compareTexture(glyph* a, glyph* b);

};
