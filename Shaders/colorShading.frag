#version 130
//Fragment shader operates on each pixel in a given polygon

//Take in given vector colors, positions, and UV
in vec2 fragPos;
in vec4 fragColor;
in vec2 fragUV;

//3 Component float vector that gets outputted to the screen for each pixel
out vec4 color;

//Uniform variable that reacts over time
//uniform float time;

//uniform sampler for the texture
uniform sampler2D textureSampler;

void main() {

    //Set textureColor using the texture and UV
    vec4 textureColor= texture(textureSampler, fragUV);

    //Create colors using time and position
    //color = vec4(fragColor.r * (cos(fragPos.x * 4 + time) + 1.0) * 0.5, 
    //            fragColor.g * (cos(fragPos.y * 8 + time) + 1.0) * 0.5, 
    //            fragColor.b * (cos(fragPos.x * 2 + time) + 1.0) * 0.5, 
    //            fragColor.a) * textureColor;

    color = fragColor * textureColor;

    return;
}