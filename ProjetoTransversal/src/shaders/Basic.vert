#version 330 core

layout (location = 0) in uvec3 vertexPos;
layout (location = 1) in uint vertexLight;
layout (location = 2) in uint vertexTextureIndex;

out vec2 TexCoordinates;
out float LightValue;
out vec3 FragPos;

uniform vec3 chunkPos;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

const float TEXTURE_ATLAS_SIZE = 8.0;
const float TEXTURE_STEP = 1.0 / TEXTURE_ATLAS_SIZE;


float extract_light_value(uint value)
{
    uint rawValue = value;
    return float(rawValue + 2u)/5.0;
}

vec2 extract_texCoords(uint texIndex)
{
    uint index = texIndex & 0x3Fu;
    float u = float(index % 8u);
    float v = float(index / 8u);
    u +=  1 * float((texIndex >> 6) & 0x01u);
    v -=  1 * float((texIndex >> 7) & 0x01u);
    return vec2(u * TEXTURE_STEP, 1.0 - ((v + 1.0) * TEXTURE_STEP));
}

vec3 extract_pos(uvec3 rawPos)
{
    vec3 fPos = vec3(rawPos)/8;

    return fPos + chunkPos;
}

void main()
{
    vec3 vertPos = extract_pos(vertexPos);
    TexCoordinates = extract_texCoords(vertexTextureIndex);

    LightValue = extract_light_value(vertexLight);

    FragPos = vec3(modelMatrix * vec4(vertPos, 1.0));
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertPos, 1.0);
}