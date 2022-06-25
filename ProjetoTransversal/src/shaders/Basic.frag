#version 330 core

in vec2 TexCoordinates;
in float LightValue;
in vec3 FragPos;
uniform sampler2D textureData;
uniform vec3 camPos;

out vec4 FragColor;

void main()
{
    vec4 texColor = vec4(0.5, 0.3, 0.4, 1.0);//texture(textureData, TexCoordinates);
    if(texColor.a < 0.2)
        discard;
    texColor = vec4(vec3(texColor) * LightValue, texColor.a);
    float dist = distance(camPos, FragPos);
    vec4 finalColor = texColor;
    if(dist > 100.0)
        finalColor = mix(texColor, vec4(0.40, 0.80, 0.9, 1.0), min((dist - 100.0)/100.0, 1.0));
    FragColor = finalColor;
}