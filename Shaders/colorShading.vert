#version 130
//Vertex shader operates on each vertex

//Input data from the VBO, each vertex is 2 floats
//Vector position and color
in vec2 vertexPos;
in vec4 vertexColor;
in vec2 vertexUV;

//Send out fragment position and color
out vec2 fragPos;
out vec4 fragColor;
out vec2 fragUV;

uniform mat4 p;

void main() {
    //Set x and y position on screen
    gl_Position.xy = (p * vec4(vertexPos, 0.0, 1.0)).xy;

    //Since we are in 2D, Z is 0
    gl_Position.z = 0.0;

    //Indicate that the coordinates are normalized
    gl_Position.w = 1.0;

    //Set fragment position, color, UV
    fragPos = vertexPos;
    fragColor = vertexColor;
    fragUV = vec2(vertexUV.x, 1.0 - vertexUV.y);
}