#version 330 core

uniform mat4 objectToWorldMat;
uniform mat4 worldToCameraMat;
uniform mat4 cameraToClipMat;
uniform vec4 lightSourcePos;

layout(location=0) in vec4 vertexPos;
layout(location=1) in vec4 vertexColor;
layout(location=2) in vec4 vertexNormal;

out vec4 fragmentColor;
out vec4 normVecCamera;
out vec4 eyeDirCamera;
out vec4 lightDirCamera;

void main()
{
    mat4 mMat = objectToWorldMat;
    mat4 mvMat = worldToCameraMat*objectToWorldMat;
    mat4 mvpMat = cameraToClipMat*worldToCameraMat*objectToWorldMat;

    vec4 vPosCamera = mvMat*vertexPos;
    vec4 vPosClip = mvpMat*vertexPos;
    vec4 lightPosCamera = worldToCameraMat*lightSourcePos;

    fragmentColor = vertexColor;
    normVecCamera = transpose( inverse(mvMat) )*vertexNormal;
    eyeDirCamera = vec4(0, 0, 0, 1)-vPosCamera;
    lightDirCamera = lightPosCamera+eyeDirCamera;

    gl_Position = vPosClip;
}

