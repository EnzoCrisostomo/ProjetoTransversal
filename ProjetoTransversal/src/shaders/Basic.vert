#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in float aLightValue;

out vec2 TexCoordinates;
out float LightValue;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
out vec3 FragPos;

void main()
{
    TexCoordinates = aTexCoord;
    LightValue = aLightValue;
    FragPos = vec3(modelMatrix * vec4(aPos, 1.0));
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(aPos, 1.0);
}