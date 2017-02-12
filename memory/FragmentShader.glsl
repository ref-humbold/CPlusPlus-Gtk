#version 330 core

uniform vec3 fragmentColor;

out vec3 outColor;

void main()
{
    outColor = fragmentColor;
}

