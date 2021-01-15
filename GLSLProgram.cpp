//File that contains functions for the GLSLProgram class

//Libraries
#include "GLSLProgram.h"

//Constructor
GLSLProgram::GLSLProgram() : _progID(0), 
                            _vertShaderID(0), 
                            _fragShaderID(0), 
                            _numAttributes(0) {
}

//Destructor
GLSLProgram::~GLSLProgram() {

}

//Function to compile shaders
void GLSLProgram::compileShaders(const std::string& vertShaderpath, const std::string& fragShaderpath) {
    
    //Set _progID
    _progID = glCreateProgram();

    //set vertShaderID and do error checking
    _vertShaderID = glCreateShader(GL_VERTEX_SHADER);
    if (!(_vertShaderID)) {
        fatalError("Vertex shader failed to be created");
    }

    //set fragShaderID and do error checking
    _fragShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    if (!(_fragShaderID)) {
        fatalError("Fragment shader failed to be created");
    }

    //Compile both vertex shader and fragment shader
    compileShader(vertShaderpath, _vertShaderID);
    compileShader(fragShaderpath, _fragShaderID);

    return;
}

//Function to link shaders
void GLSLProgram::linkShaders() {

    //Attach shaders to _progID
    glAttachShader(_progID, _vertShaderID);
    glAttachShader(_progID, _fragShaderID);

    //Link the program
    glLinkProgram(_progID);

    //Error checking for shader linking success
    GLint isLinked = 0;
    glGetProgramiv(_progID, GL_LINK_STATUS, (int *)&isLinked);
    if (isLinked == GL_FALSE) {
        GLint maxLen = 0;
        glGetProgramiv(_progID, GL_INFO_LOG_LENGTH, &maxLen);

        std::vector<char> errorLog(maxLen);
        glGetProgramInfoLog(_progID, maxLen, &maxLen, &errorLog[0]);

        glDeleteProgram(_progID);
        glDeleteShader(_vertShaderID);
        glDeleteShader(_fragShaderID);

        std::printf("%s\n", &errorLog[0]);
        fatalError("Shaders failed to link");

    }

    //Detach shaders from _progID and delete them
    glDetachShader(_progID, _vertShaderID);
    glDetachShader(_progID, _fragShaderID);
    glDeleteShader(_vertShaderID);
    glDeleteShader(_fragShaderID);

    return;
}

//Function to add attributes
void GLSLProgram::addAttribute(const std::string& attrName) {
    
    //Bind attributes and increment _numAttributes
    glBindAttribLocation(_progID, _numAttributes, attrName.c_str());
    _numAttributes++;

    return;
}

//Function to get the uniform Location
GLint GLSLProgram::getuniformLocation(const std::string& uniformName) {
    GLint location = glGetUniformLocation(_progID, uniformName.c_str());

    //Error checking
    if (location == GL_INVALID_INDEX) {
        fatalError("Uniform " + uniformName + " not found in shader");
    }

    return location;
}

//Function to enable shaders
void GLSLProgram::enable() {
    //Set use program to _progID and enable vertex attributes
    glUseProgram(_progID);
    for (int i = 0; i < _numAttributes; i++) {
        glEnableVertexAttribArray(i);
    }
    return;
}

//Function to disable shaders
void GLSLProgram::disable() {
    //Set use program to 0 and disable vertex attributes
    glUseProgram(0);
    for (int i = 0; i < _numAttributes; i++) {
        glDisableVertexAttribArray(i);
    }
    return;
}

//Function to compile single shader files
void GLSLProgram::compileShader(const std::string& filePath, GLuint& id) {

    //Variables of ifstream
    std::string fileContents = "";
    std::string line;

    //Set ifstream and do error checking
    std::ifstream shaderFile(filePath);
    if (shaderFile.fail()) {
        perror(filePath.c_str());
        fatalError("Failed to open " + filePath);
    }

    //While lines exist in file, add it to fileContents
    while (std::getline(shaderFile, line)) {
        fileContents += line + "\n";
    }

    //Close shader file
    shaderFile.close();

    //Sset shader source
    const char* contentsPtr = fileContents.c_str();
    glShaderSource(id, 1, &contentsPtr, nullptr);

    //Compile shader using id
    glCompileShader(id);

    //Error checking for shaders compilation success
    GLint success = 0;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
        GLint maxLen = 0;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLen);

        std::vector<char> errorLog(maxLen);
        glGetShaderInfoLog(id, maxLen, &maxLen, &errorLog[0]);

        glDeleteShader(id);

        std::printf("%s\n", &errorLog[0]);
        fatalError("Shader " + filePath + " failed to compile");
    }

    return;
}