//Functions for sprite batch class

//Libraries
#include "spriteBatch.h"

//Constructor
spriteBatch::spriteBatch() : _vbo(0), 
                            _vao(0) {

}

//Destructor
spriteBatch::~spriteBatch() {

}

//Function to initialize the class
void spriteBatch::init() {

    //Create vertex array
    createVertexArray();

    return;
}

//Function to Set up class for drawing
void spriteBatch::begin(glyphSortType sortType/* = glyphSortType::TEXTURE*/) {

    //Set sort type and clear prior render batches
    _sortType = sortType;
    _renderbatches.clear();

    //Clear data leaks
    for (int i = 0; i < _glyphs.size(); i++) {
        delete _glyphs[i];
    }

    //Clear glyphs
    _glyphs.clear();

    return;
}

//Function to maintain post processing of batch
void spriteBatch::end() {

    //Sort and create the batches
    sortGlyphs();
    createRenderBatches();

    return;
}

//Function to Draw sprites to batch
void spriteBatch::draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color& color) {

    //Create new glyph pointer and set values
    glyph* newGlyph = new glyph;
    newGlyph->texture = texture;
    newGlyph->depth = depth;

    //Set all 4 vertex corners to set values
    newGlyph->topLeft.color = color;
    newGlyph->topLeft.setPos(destRect.x, destRect.y + destRect.w);
    newGlyph->topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

    newGlyph->botLeft.color = color;
    newGlyph->botLeft.setPos(destRect.x, destRect.y);
    newGlyph->botLeft.setUV(uvRect.x, uvRect.y);

    newGlyph->topRight.color = color;
    newGlyph->topRight.setPos(destRect.x + destRect.z, destRect.y + destRect.w);
    newGlyph->topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);

    newGlyph->botRight.color = color;
    newGlyph->botRight.setPos(destRect.x + destRect.z, destRect.y);
    newGlyph->botRight.setUV(uvRect.x + uvRect.z, uvRect.y);

    //Push back the new glyph
    _glyphs.push_back(newGlyph);

    return;
}

//Function to render batch to screen
void spriteBatch::renderBatch() {

    //Bind _vao
    glBindVertexArray(_vao);

    //Bind and draw batches
    for (int i = 0; i < _renderbatches.size(); i++) {
        glBindTexture(GL_TEXTURE_2D, _renderbatches[i].texture);

        glDrawArrays(GL_TRIANGLES, _renderbatches[i].offset, _renderbatches[i].numVertices);
    }

    //Unbing the vertex array
    glBindVertexArray(0);

    return;
}

void spriteBatch::createRenderBatches() {

    //variables
    int offset = 0;
    int currVertex = 0;

    //Create a vector of vertices and resize it accordingly
    std::vector<vertex> vertices;
    vertices.resize(_glyphs.size() * 6);

    //Check if glyphs is empty
    if (_glyphs.empty()) {
        return;
    }

    //Emplace back the render batches to push glyphs
    _renderbatches.emplace_back(offset, 6, _glyphs[0]->texture);

    //Set the vertices current vertex corners
    vertices[currVertex++] = _glyphs[0]->topLeft;
    vertices[currVertex++] = _glyphs[0]->botLeft;
    vertices[currVertex++] = _glyphs[0]->botRight;
    vertices[currVertex++] = _glyphs[0]->botRight;
    vertices[currVertex++] = _glyphs[0]->topRight;
    vertices[currVertex++] = _glyphs[0]->topLeft;

    //Increment the offset
    offset += 6;

    //For loop to go through each set of glyphs
    for (int currGlyph = 1; currGlyph < _glyphs.size(); currGlyph++) {

        //Check if new glyph is used
        if (_glyphs[currGlyph]->texture != _glyphs[currGlyph - 1]->texture) {
          _renderbatches.emplace_back(offset, 6, _glyphs[currGlyph]->texture);
        } else {
            _renderbatches.back().numVertices += 6;
        }

        //Set the vertices current vertex corners
        vertices[currVertex++] = _glyphs[currGlyph]->topLeft;
        vertices[currVertex++] = _glyphs[currGlyph]->botLeft;
        vertices[currVertex++] = _glyphs[currGlyph]->botRight;
        vertices[currVertex++] = _glyphs[currGlyph]->botRight;
        vertices[currVertex++] = _glyphs[currGlyph]->topRight;
        vertices[currVertex++] = _glyphs[currGlyph]->topLeft;

        //Increment the offset
        offset += 6;
    }
    
    //Bind the buffer
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);

    //Orphan the buffer
    glBufferData(GL_ARRAY_BUFFER, (vertices.size() * sizeof(vertex)), nullptr, GL_DYNAMIC_DRAW);

    //Upload the buffer
    glBufferSubData(GL_ARRAY_BUFFER, 0, (vertices.size() * sizeof(vertex)), vertices.data());

    return;
}

//Function to create vertex array
void spriteBatch::createVertexArray() {

    //Check if vao has been initialized, if not initialize it 
    if (!(_vao)) {
        glGenVertexArrays(1, &_vao);
    }
    glBindVertexArray(_vao);

    //Check if vbo has been initialized, if not initialize it 
    if (!(_vbo)) {
        glGenBuffers(1, &_vbo);
    }
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);

    //Enable the vertex attributes
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    
    //Position attribute pointer
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, pos));
    //Color attribute pointer
    glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(vertex), (void*)offsetof(vertex, color));
    //UV attribute pointer
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, uv));

    //Unbind vertex array
    glBindVertexArray(0);

    return;
}

void spriteBatch::sortGlyphs() {

    //Switch case to stable sort accordingly
    switch (_sortType) {
        case glyphSortType::BACK_TO_FRONT:
            std::stable_sort(_glyphs.begin(), _glyphs.end(), compareBacktoFront);
            break;

        case glyphSortType::FRONT_TO_BACK:
            std::stable_sort(_glyphs.begin(), _glyphs.end(), compareFrontToBack);
            break;

        case glyphSortType::TEXTURE:
            std::stable_sort(_glyphs.begin(), _glyphs.end(), compareTexture);
            break;
    }
    return;
}

//Functions to compare glyphs accordingly
bool spriteBatch::compareBacktoFront(glyph* a, glyph* b) {
    return (a->depth > b->depth);
}

bool spriteBatch::compareFrontToBack(glyph* a, glyph* b) {
    return (a->depth < b->depth);
}

bool spriteBatch::compareTexture(glyph* a, glyph* b) {
    return (a->texture < b->texture);
}