#version 330 core

uniform vec2 scale;
uniform vec2 transform;

layout(location=0) in vec2 vertexPos;

void main()
{
    gl_Position.xy = scale*(vertexPos+transform);
    gl_Position.z = 0.0;
    gl_Position.w = 1.0;
}

