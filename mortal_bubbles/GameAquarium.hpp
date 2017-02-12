#ifndef GAME_AQUARIUM_HPP
#define GAME_AQUARIUM_HPP

#include <cstdlib>
#include <iostream>
#include <cmath>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

using namespace glm;

class GameAquarium
{
    private:
    const GLfloat vbDataCube[56];
    const GLfloat cbDataCube[56];
    GLfloat nbDataCube[56];
    const GLushort ibDataCube[36];
    GLuint vertexBufferCube;
    GLuint colorBufferCube;
    GLuint normalBufferCube;
    GLuint indexBufferCube;

    mat4 sc;
    mat4 rt;
    mat4 tr;

    public:
    GameAquarium() :
        vbDataCube{0.5f, 0.5f, 0.5f, 1.0f,    //0
                   -0.5f, 0.5f, 0.5f, 1.0f,
                   -0.5f, -0.5f, 0.5f, 1.0f,
                   0.5f, -0.5f, 0.5f, 1.0f,
                   0.5f, 0.5f, -0.5f, 1.0f,
                   -0.5f, 0.5f, -0.5f, 1.0f,
                   -0.5f, -0.5f, -0.5f, 1.0f,
                   0.5f, -0.5f, -0.5f, 1.0f,
                   0.0f, 0.0f, 0.5f, 1.0f,    // 8
                   0.0f, 0.0f, -0.5f, 1.0f,
                   0.0f, 0.5f, 0.0f, 1.0f,
                   0.0f, -0.5f, 0.0f, 1.0f,
                   0.5f, 0.0f, 0.0f, 1.0f,
                   -0.5f, 0.0f, 0.0f, 1.0f},
        cbDataCube{0.0f, 0.0f, 1.0f, 0.1f,  //0
                   0.0f, 0.0f, 1.0f, 0.1f,
                   0.0f, 0.0f, 1.0f, 0.1f,
                   0.0f, 0.0f, 1.0f, 0.1f,
                   0.0f, 0.0f, 1.0f, 0.1f,
                   0.0f, 0.0f, 1.0f, 0.1f,
                   0.0f, 0.0f, 1.0f, 0.1f,
                   0.0f, 0.0f, 1.0f, 0.1f,
                   0.0f, 0.5f, 1.0f, 0.1f,  //8
                   0.0f, 0.5f, 1.0f, 0.1f,
                   0.0f, 0.5f, 1.0f, 0.1f,
                   0.0f, 0.5f, 1.0f, 0.1f,
                   0.0f, 0.5f, 1.0f, 0.1f,
                   0.0f, 0.5f, 1.0f, 0.1f},
        nbDataCube{0.0f, 0.0f, 0.0f, 0.0f,  //0
                   0.0f, 0.0f, 0.0f, 0.0f,
                   0.0f, 0.0f, 0.0f, 0.0f,
                   0.0f, 0.0f, 0.0f, 0.0f,
                   0.0f, 0.0f, 0.0f, 0.0f,
                   0.0f, 0.0f, 0.0f, 0.0f,
                   0.0f, 0.0f, 0.0f, 0.0f,
                   0.0f, 0.0f, 0.0f, 0.0f,
                   0.0f, 0.0f, 0.0f, 0.0f,  //8
                   0.0f, 0.0f, 0.0f, 0.0f,
                   0.0f, 0.0f, 0.0f, 0.0f,
                   0.0f, 0.0f, 0.0f, 0.0f,
                   0.0f, 0.0f, 0.0f, 0.0f,
                   0.0f, 0.0f, 0.0f, 0.0f},
        ibDataCube{8, 0, 3, 2, 1, 0,
                   9, 7, 4, 5, 6, 7,
                   10, 4, 0, 1, 5, 4,
                   11, 6, 2, 3, 7, 6,
                   12, 0, 4, 7, 3, 0,
                   13, 5, 1, 2, 6, 5},
        sc{mat4( vec4(1.0f, 0.0f, 0.0f, 0.0f),
                 vec4(0.0f, 1.0f, 0.0f, 0.0f),
                 vec4(0.0f, 0.0f, 1.0f, 0.0f),
                 vec4(0.0f, 0.0f, 0.0f, 1.0f) )},
        rt{mat4( vec4(1.0f, 0.0f, 0.0f, 0.0f),
                 vec4(0.0f, 1.0f, 0.0f, 0.0f),
                 vec4(0.0f, 0.0f, 1.0f, 0.0f),
                 vec4(0.0f, 0.0f, 0.0f, 1.0f) )},
        tr{mat4( vec4(1.0f, 0.0f, 0.0f, 0.0f),
                 vec4(0.0f, 1.0f, 0.0f, 0.0f),
                 vec4(0.0f, 0.0f, 1.0f, 0.0f),
                 vec4(0.0f, 0.0f, 0.0f, 1.0f) )}
    {
        countNormals();

        glGenBuffers(1, &vertexBufferCube);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferCube);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vbDataCube), vbDataCube, GL_STATIC_DRAW);

        glGenBuffers(1, &colorBufferCube);
        glBindBuffer(GL_ARRAY_BUFFER, colorBufferCube);
        glBufferData(GL_ARRAY_BUFFER, sizeof(cbDataCube), cbDataCube, GL_STATIC_DRAW);

        glGenBuffers(1, &normalBufferCube);
        glBindBuffer(GL_ARRAY_BUFFER, normalBufferCube);
        glBufferData(GL_ARRAY_BUFFER, sizeof(nbDataCube), nbDataCube, GL_STATIC_DRAW);

        glGenBuffers(1, &indexBufferCube);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferCube);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ibDataCube), ibDataCube, GL_STATIC_DRAW);
    }

    void drawCube(GLuint pID, mat4 worldToCamera, mat4 cameraToClip, vec4 lightSource);
    GLfloat getSide();
    vec3 normalVec(GLushort i1, GLushort i2, GLushort i3);
    void countNormals();
};

#endif

