#version 330 core

layout (location = 0) in uint vertex;
//layout (location = 1) in vec2 aTexCoord;
//layout (location = 2) in float aLightValue;

out vec2 TexCoordinates;
out float LightValue;

uniform vec3 chunkPos;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
out vec3 FragPos;

float extract_light_value(uint vert)
{
    uint rawValue = vertex >> 18u;
    rawValue &= 0x3u;
    return float(rawValue + 2u)/5.0;
}

const float spacing = 1.0 / 8.0;
vec2 extract_texCoords(uint vert)
{
    uint index = vertex >> 12u;
    index &= 0x3Fu;
    float u = float(index % 8u);
    float v = float(index / 8u);
    return vec2(spacing * u, spacing * v);
}

vec3 extract_pos(uint vert)
{
    float x = float((vertex >> 0u) & 0xFu);
    float y = float((vertex >> 4u) & 0xFu);
    float z = float((vertex >> 8u) & 0xFu);

    return vec3(x, y, z) + (chunkPos * 16.0);
}

void main()
{
    TexCoordinates = extract_texCoords(vertex);
    LightValue = extract_light_value(vertex);
    vec3 vertPos = extract_pos(vertex);

    FragPos = vec3(modelMatrix * vec4(vertPos, 1.0));
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertPos, 1.0);
}