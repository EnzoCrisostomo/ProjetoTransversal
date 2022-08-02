#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec4 aColor;

uniform mat4 projectionMatrix;

out vec2 TexCoordinates;

void main()
{
    TexCoordinates = aTexCoord;
    gl_Position = projectionMatrix * vec4(aPos, 1.0);
}