#include "GamePlayer.hpp"

using namespace glm;

void GamePlayer::drawPlayer(GLuint pID, mat4 worldToCamera, mat4 cameraToClip, vec4 lightSource)
{
    mat4 objectToWorld = tr*rt*sc;

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferPlayer);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (void *)0);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colorBufferPlayer);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void *)0);

    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, normalBufferPlayer);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, (void *)0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferPlayer);

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
    {
        int ix = (42*i+22)*sizeof(unsigned short);

        glDrawElements(GL_TRIANGLE_STRIP, 42, GL_UNSIGNED_SHORT, (void*)ix);
    }

    glDrawElements( GL_TRIANGLE_FAN, 22, GL_UNSIGNED_SHORT, (void*)( 358*sizeof(unsigned short) ) );

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
}

void GamePlayer::restart(GLfloat pos)
{
    tr[3][0] = pos;
    tr[3][1] = pos;
    tr[3][2] = pos;
}

void GamePlayer::move(vec3 v)
{
    tr[3][0] += v[0]*velocity;
    tr[3][1] += v[1]*velocity;
    tr[3][2] += v[2]*velocity;
}

std::pair<GLfloat, vec3> GamePlayer::getRadPos()
{
    return std::make_pair(sc[0][0], vec3( tr[3][0], tr[3][1], tr[3][2] ) );
}

vec3 GamePlayer::normalVec(GLushort i1, GLushort i2, GLushort i3)
{
    vec3 u1 = vec3( vbDataPlayer[4*i1], vbDataPlayer[4*i1+1], vbDataPlayer[4*i1+2] );
    vec3 u2 = vec3( vbDataPlayer[4*i2], vbDataPlayer[4*i2+1], vbDataPlayer[4*i2+2] );
    vec3 u3 = vec3( vbDataPlayer[4*i3], vbDataPlayer[4*i3+1], vbDataPlayer[4*i3+2] );
    vec3 u12 = u2-u1;
    vec3 u13 = u3-u1;

    return normalize( cross(u12, u13) );
}

void GamePlayer::countNormals()
{
    auto count = [=](int i1, int i2, int i3)
        {
            GLushort x1 = ibDataPlayer[i1], x2 = ibDataPlayer[i2], x3 = ibDataPlayer[i3];
            vec3 norm = normalVec(x1, x2, x3);

            nbDataPlayer[4*x1] += norm[0];
            nbDataPlayer[4*x1+1] += norm[1];
            nbDataPlayer[4*x1+2] += norm[2];
            nbDataPlayer[4*x2] += norm[0];
            nbDataPlayer[4*x2+1] += norm[1];
            nbDataPlayer[4*x2+2] += norm[2];
            nbDataPlayer[4*x3] += norm[0];
            nbDataPlayer[4*x3+1] += norm[1];
            nbDataPlayer[4*x3+2] += norm[2];
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
        vec3 n = normalize( vec3( nbDataPlayer[4*i], nbDataPlayer[4*i+1], nbDataPlayer[4*i+2] ) );

        nbDataPlayer[4*i] = n[0];
        nbDataPlayer[4*i+1] = n[1];
        nbDataPlayer[4*i+2] = n[2];
    }
}
