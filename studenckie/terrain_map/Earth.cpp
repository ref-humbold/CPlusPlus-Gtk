#include "Earth.hpp"

using namespace glm;

Earth::Earth() :
    numLongs{36},
    numLats{17}
{
    auto push_point = [=](GLfloat longitude, GLfloat latitude)
        {
            vbData.push_back(longitude);
            vbData.push_back(latitude);
        };

    push_point(0.0f, 90.0f);

    for(int lt = 80; lt >= -80; lt -= 10)
        for(int lg = -170; lg <= 180; lg += 10)
            push_point(lg, lt);

    push_point(0.0f, -90.0f);

    for(int i = 0; i < numLats; ++i)
        for(int j = 1; j <= numLongs; ++j)
            ibData.push_back(numLongs*i+j);

    for(int j = 1; j <= numLongs; ++j)
    {
        ibData.push_back(0);

        for(int i = 0; i < numLats; ++i)
            ibData.push_back(numLongs*i+j);

        ibData.push_back(numLongs*numLats+1);
    }

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vbData.size()*sizeof(GLfloat), &vbData[0], GL_STATIC_DRAW);

    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, ibData.size()*sizeof(GLuint), &ibData[0], GL_STATIC_DRAW);
}

void Earth::draw(GLuint pID, mat4 worldToCamera)
{
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void *)0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

    GLint worldToCameraMat = glGetUniformLocation(pID, "worldToCameraMat");

    glUniformMatrix4fv(worldToCameraMat, 1, GL_FALSE, &worldToCamera[0][0]);

    for(int i = 0; i < numLats; ++i)
    {
        int ix = i*numLongs*sizeof(GLuint);

        glDrawElements(GL_LINE_LOOP, numLongs, GL_UNSIGNED_INT, (void*)ix);
    }

    int longitsStart = numLongs*numLats*sizeof(GLuint);

    for(int i = 0; i < numLongs; ++i)
    {
        int ix = longitsStart+i*(numLats+2)*sizeof(GLuint);

        glDrawElements(GL_LINE_STRIP, numLats+2, GL_UNSIGNED_INT, (void*)ix);
    }

    glDisableVertexAttribArray(0);
}
