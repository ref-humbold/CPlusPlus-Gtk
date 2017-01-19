#include <cstdlib>
#include <iostream>
#include <cmath>
#include <tuple>
#include <vector>
#include <algorithm>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "GameBubble.hpp"

using namespace glm;

void GameBubble::drawAllBubbles(GLuint pID, mat4 worldToCamera, mat4 cameraToClip, vec4 lightSource)
{
    for(auto & b : elements)
    {
        setColor( std::get<2>(b) );
        drawBubble( pID, worldToCamera, cameraToClip, lightSource, std::get<0>(b), std::get<1>(b) );
    }

    setColor( std::get<2>(endGameBubble) );
    drawBubble( pID, worldToCamera, cameraToClip, lightSource, std::get<0>(endGameBubble),
        std::get<1>(endGameBubble) );
}

void GameBubble::drawBubble(GLuint pID, mat4 worldToCamera, mat4 cameraToClip, vec4 lightSource,
    GLfloat radius, vec3 pos)
{
    for(int i = 0; i < 3; ++i)
    {
        sc[i][i] = radius;
        tr[3][i] = pos[i];
    }

    mat4 objectToWorld = tr*rt*sc;

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferBubble);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (void *)0);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colorBufferBubble);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cbDataBubble), cbDataBubble, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void *)0);

    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, normalBufferBubble);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, (void *)0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferBubble);

    GLint objectToWorldMat = glGetUniformLocation(pID, "objectToWorldMat");
    GLint worldToCameraMat = glGetUniformLocation(pID, "worldToCameraMat");
    GLint cameraToClipMat = glGetUniformLocation(pID, "cameraToClipMat");
    GLint lightSourcePos = glGetUniformLocation(pID, "lightSourcePos");

    glUniformMatrix4fv( objectToWorldMat, 1, GL_FALSE, &objectToWorld[0][0] );
    glUniformMatrix4fv( worldToCameraMat, 1, GL_FALSE, &worldToCamera[0][0] );
    glUniformMatrix4fv( cameraToClipMat, 1, GL_FALSE, &cameraToClip[0][0] );
    glUniform4fv( lightSourcePos, 1, &lightSource[0] );

    glDrawElements(GL_TRIANGLE_FAN, 22, GL_UNSIGNED_SHORT, (void*)0);

    for(int i = 0; i < 8; ++i)
        glDrawElements( GL_TRIANGLE_STRIP, 42, GL_UNSIGNED_SHORT, (void*)( (42*i+22)*sizeof(unsigned short) ) );

    glDrawElements( GL_TRIANGLE_FAN, 22, GL_UNSIGNED_SHORT, (void*)( 358*sizeof(unsigned short) ) );

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
}

void GameBubble::setColor(vec3 color)
{
    for(int i = 0; i < 182; ++i)
    {
        cbDataBubble[i*4] = color[0];
        cbDataBubble[i*4+1] = color[1];
        cbDataBubble[i*4+2] = color[2];
    }
}

void GameBubble::showUp(GLfloat side)
{
    auto collides = [=](GLfloat rad, vec3 pos)
        {
            for(auto & bub : elements)
                if(distance(std::get<1>(bub), pos) <= std::get<0>(bub)+rad)
                    return true;

            return false;
        };

    vec3 pos, col;
    GLfloat rad;
    int mxMod = 9;
    bool extra = rand()%50 == 0;

    do
    {
        rad = (rand()%11+5)/100.0;
        pos = vec3( (rand()%mxMod-mxMod/2)/10.0, -side, (rand()%mxMod-mxMod/2)/10.0 );
    }
    while( collides(rad, pos) );

    ++countElems;

    if(extra)
    {
        col = vec3(1.0f, 1.0f, 1.0f);
        elements.push_back( std::make_tuple(rad, pos, col, countElems) );
    }
    else
    {
        col = coloring[rand()%coloring.size()];
        elements.push_back( std::make_tuple(rad, pos, col, -countElems) );
    }
}

void GameBubble::move(GLfloat delta, GLfloat side)
{
    auto mapping = [=](std::tuple <GLfloat, vec3, vec3, int> p)
        {
            std::get<0>(p) *= 1.002;
            std::get<1>(p)[1] += delta*velocity;

            return p;
        };

    auto isOut = [=](std::tuple <GLfloat, vec3, vec3, int> b)
    {
        return std::get<1>(b)[1] >= side;
    };

    std::transform(elements.begin(), elements.end(), elements.begin(), mapping);
    elements.remove_if(isOut);
}

vec3 GameBubble::normalVec(GLushort i1, GLushort i2, GLushort i3)
{
    vec3 u1 = vec3( vbDataBubble[4*i1], vbDataBubble[4*i1+1], vbDataBubble[4*i1+2] );
    vec3 u2 = vec3( vbDataBubble[4*i2], vbDataBubble[4*i2+1], vbDataBubble[4*i2+2] );
    vec3 u3 = vec3( vbDataBubble[4*i3], vbDataBubble[4*i3+1], vbDataBubble[4*i3+2] );
    vec3 u12 = u2-u1;
    vec3 u13 = u3-u1;

    return normalize( cross(u12, u13) );
}

void GameBubble::countNormals()
{
    auto count = [=](int i1, int i2, int i3)
        {
            GLushort x1 = ibDataBubble[i1], x2 = ibDataBubble[i2], x3 = ibDataBubble[i3];
            vec3 norm = normalVec(x1, x2, x3);

            nbDataBubble[4*x1] += norm[0];
            nbDataBubble[4*x1+1] += norm[1];
            nbDataBubble[4*x1+2] += norm[2];
            nbDataBubble[4*x2] += norm[0];
            nbDataBubble[4*x2+1] += norm[1];
            nbDataBubble[4*x2+2] += norm[2];
            nbDataBubble[4*x3] += norm[0];
            nbDataBubble[4*x3+1] += norm[1];
            nbDataBubble[4*x3+2] += norm[2];
        };

    for(int i = 1; i < 21; ++i)
        count(0, i, i+1);

    for(int i = 0; i < 8; ++i)
    {
        int d = 42*i+22;

        for(int j = 0; j < 40; j+=2)
        {
            count(d+j, d+j+1, d+j+2);
            count(d+j+1, d+j+3, d+j+2);
        }
    }

    for(int i = 1; i < 21; ++i)
        count(358, 358+i, 358+i+1);

    for(int i = 0; i < 182; ++i)
    {
        vec3 n = normalize( vec3( nbDataBubble[4*i], nbDataBubble[4*i+1], nbDataBubble[4*i+2] ) );

        nbDataBubble[4*i] = n[0];
        nbDataBubble[4*i+1] = n[1];
        nbDataBubble[4*i+2] = n[2];
    }
}
