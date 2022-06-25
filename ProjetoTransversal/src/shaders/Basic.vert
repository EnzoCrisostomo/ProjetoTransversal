#version 330 core

layout (location = 0) in uint vertex;

out vec2 TexCoordinates;
out float LightValue;
out vec3 FragPos;

uniform vec3 chunkPos;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

const float TEXTURE_ATLAS_SIZE = 8.0;
const float TEXTURE_STEP = 1.0 / TEXTURE_ATLAS_SIZE;


float extract_light_value(uint vert)
{
    uint rawValue = (vert >> 18u) & 0x3u;
    return float(rawValue + 2u)/5.0;
}

vec2 extract_texCoords(uint vert)
{
    uint index = (vert >> 20u) & 0x3Fu;
    float u = float(index % 8u);
    float v = float(index / 8u);
    u +=  1 * float((vert >> 26) & 0x01u);
    v -=  1 * float((vert >> 27) & 0x01u);
    return vec2(u * TEXTURE_STEP, 1.0 - ((v + 1.0) * TEXTURE_STEP));
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
    TexCoordinates = extract_texCoords(vertex);

    LightValue = extract_light_value(vertex);

    FragPos = vec3(modelMatrix * vec4(vertPos, 1.0));
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertPos, 1.0);
}