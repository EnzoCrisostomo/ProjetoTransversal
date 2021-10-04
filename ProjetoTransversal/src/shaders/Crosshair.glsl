#shader vertex
#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 projectionMatrix;

void main()
{
    gl_Position = projectionMatrix * vec4(aPos, 1.0);
}

#shader fragment
#version 330 core

out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}