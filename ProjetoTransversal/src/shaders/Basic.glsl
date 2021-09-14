#shader vertex
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoordinates;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main()
{
    TexCoordinates = aTexCoord; 
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(aPos, 1.0);
}

#shader fragment
#version 330 core

in vec2 TexCoordinates;
uniform sampler2D textureData;

out vec4 FragColor;

void main()
{
    FragColor = texture(textureData, TexCoordinates);
}