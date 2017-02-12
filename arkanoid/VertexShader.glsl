#version 330 core

uniform mat2 scaleMat;
uniform mat2 rotateMat;
uniform vec2 transformVec;

layout(location=0) in vec2 vertexPos;
layout(location=1) in vec3 vertexColor;

out vec3 fragmentColor;

void main()
{
    gl_Position.xy = rotateMat*scaleMat*vertexPos+transformVec;
    gl_Position.z = 0.0;
    gl_Position.w = 1.0;
    fragmentColor = vertexColor;
}

