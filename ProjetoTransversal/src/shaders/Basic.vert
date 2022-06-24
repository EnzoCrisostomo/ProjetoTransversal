#version 330 core

//layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
//layout (location = 2) in float aLightValue;
layout (location = 3) in uint vertex;

out vec2 TexCoordinates;
out float LightValue;

uniform vec3 chunkPos;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
out vec3 FragPos;

float extract_light_value(uint vert)
{
    uint rawValue = (vert >> 18u) & 0x3u;
    return float(rawValue + 2u)/5.0;
}

const float spacing = 1.0 / 8.0;
vec2 extract_texCoords(uint vert)
{
    uint index = (vertex >> 20u) & 0x3Fu;
    float u = float(index % 8u);
    float v = float(index / 8u);
    return vec2(spacing * u, spacing * v);
}

vec3 extract_pos(uint vert)
{
    float x = float(vert & 0x3Fu);
    float y = float((vert & 0xFC0u) >> 6u);
    float z = float((vert & 0x3F000u) >> 12u);

    return vec3(x, y, z) + chunkPos;
}

void main()
{
    vec3 vertPos = extract_pos(vertex);
    TexCoordinates = aTexCoord;//extract_texCoords(vertex);

    LightValue = extract_light_value(vertex);

    FragPos = vec3(modelMatrix * vec4(vertPos, 1.0));
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertPos, 1.0);
}