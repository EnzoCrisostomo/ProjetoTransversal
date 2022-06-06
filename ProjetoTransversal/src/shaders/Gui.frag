#version 330 core

in vec2 TexCoordinates;

uniform sampler2D textureData;

out vec4 FragColor;

void main()
{
    vec4 texColor = texture(textureData, TexCoordinates);
    if(texColor.a < 0.1)
        discard;
    FragColor = texColor;
}