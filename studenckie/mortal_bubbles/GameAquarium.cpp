#include "GameAquarium.hpp"

using namespace glm;

void GameAquarium::drawCube(GLuint pID, mat4 worldToCamera, mat4 cameraToClip, vec4 lightSource)
{
    mat4 objectToWorld = tr*rt*sc;

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferCube);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (void *)0);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colorBufferCube);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void *)0);

    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, normalBufferCube);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, (void *)0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferCube);

    GLint objectToWorldMat = glGetUniformLocation(pID, "objectToWorldMat");
    GLint worldToCameraMat = glGetUniformLocation(pID, "worldToCameraMat");
    GLint cameraToClipMat = glGetUniformLocation(pID, "cameraToClipMat");
    GLint lightSourcePos = glGetUniformLocation(pID, "lightSourcePos");

    glUniformMatrix4fv( objectToWorldMat, 1, GL_FALSE, &objectToWorld[0][0] );
    glUniformMatrix4fv( worldToCameraMat, 1, GL_FALSE, &worldToCamera[0][0] );
    glUniformMatrix4fv( cameraToClipMat, 1, GL_FALSE, &cameraToClip[0][0] );
    glUniform4fv( lightSourcePos, 1, &lightSource[0] );

    for(int i = 0; i < 6; ++i)
    {
        int ix = 6*i*sizeof(unsigned short);

        glDrawElements(GL_TRIANGLE_FAN, 6, GL_UNSIGNED_SHORT, (void*)ix);
    }

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
}

GLfloat GameAquarium::getSide()
{
    return sc[0][0]*vbDataCube[0];
}

vec3 GameAquarium::normalVec(GLushort i1, GLushort i2, GLushort i3)
{
    vec3 u1 = vec3( vbDataCube[4*i1], vbDataCube[4*i1+1], vbDataCube[4*i1+2] );
    vec3 u2 = vec3( vbDataCube[4*i2], vbDataCube[4*i2+1], vbDataCube[4*i2+2] );
    vec3 u3 = vec3( vbDataCube[4*i3], vbDataCube[4*i3+1], vbDataCube[4*i3+2] );
    vec3 u12 = u2-u1;
    vec3 u13 = u3-u1;

    return normalize( cross(u12, u13) );
}

void GameAquarium::countNormals()
{
    for(int i = 0; i < 6; ++i)
        for(int j = 1; j < 5; ++j)
        {
            GLushort x1 = ibDataCube[6*i], x2 = ibDataCube[6*i+j], x3 = ibDataCube[6*i+j+1];
            vec3 norm = normalVec(x1, x2, x3);

            nbDataCube[4*x1] += norm[0];
            nbDataCube[4*x1+1] += norm[1];
            nbDataCube[4*x1+2] += norm[2];
            nbDataCube[4*x2] += norm[0];
            nbDataCube[4*x2+1] += norm[1];
            nbDataCube[4*x2+2] += norm[2];
            nbDataCube[4*x3] += norm[0];
            nbDataCube[4*x3+1] += norm[1];
            nbDataCube[4*x3+2] += norm[2];
        }

    for(int i = 0; i < 14; ++i)
    {
        vec3 n = normalize( vec3( nbDataCube[4*i], nbDataCube[4*i+1], nbDataCube[4*i+2] ) );

        nbDataCube[4*i] = n[0];
        nbDataCube[4*i+1] = n[1];
        nbDataCube[4*i+2] = n[2];
    }
}
