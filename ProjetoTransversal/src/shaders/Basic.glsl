#shader vertex
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in float aLightValue;

out vec2 TexCoordinates;
out float LightValue;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main()
{
    TexCoordinates = aTexCoord;
    LightValue = aLightValue;
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(aPos, 1.0);
}

#shader fragment
#version 330 core

in vec2 TexCoordinates;
in float LightValue;
uniform sampler2D textureData;

out vec4 FragColor;

void main()
{
    vec4 texColor = texture(textureData, TexCoordinates);
    if(texColor.a < 0.2)
        discard;
    texColor = vec4(vec3(texColor) * LightValue, texColor.a);
    FragColor = texColor;
}