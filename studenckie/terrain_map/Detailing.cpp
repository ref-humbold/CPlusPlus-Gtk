#include "Detailing.hpp"

Detailing::Detailing() :
    detailsLevel{0},
    detailsSteps{1, 3, 6, 10, 15, 20, 30, 40, 60}
{
    vbData.reserve(SIDE*SIDE);

    for(int lt = SIDE-1; lt >= 0; --lt)
        for(int lg = 0; lg < SIDE; ++lg)
        {
            vbData.push_back(lg/1200.0f);
            vbData.push_back(lt/1200.0f);
        }

    for(int step : detailsSteps)
    {
        long long int trinum = 0LL;
        std::vector<GLuint> indices;

        for(int i = step; i < SIDE; i += step)
        {
            for(int j = 0; j < SIDE; j += step)
            {
                indices.push_back(SIDE*(i-step)+j);
                indices.push_back(SIDE*i+j);
                trinum += 2LL;
            }

            trinum -= 2LL;
        }

        ibData.push_back(indices);
        triangles.push_back(trinum);
    }

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vbData.size()*sizeof(GLfloat), &vbData[0], GL_STATIC_DRAW);

    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, ibData[detailsLevel].size()*sizeof(GLuint),
        &ibData[detailsLevel][0], GL_STATIC_DRAW);
}

long long int Detailing::getTriangles()
{
    return triangles[detailsLevel];
}

int Detailing::getLOD()
{
    return detailsLevel;
}

void Detailing::setLOD(int degLOD)
{
    int levelsMaxNum = detailsSteps.size()-1;
    int oldLOD = detailsLevel;

    detailsLevel = degLOD;
    detailsLevel = std::min(detailsLevel, levelsMaxNum);
    detailsLevel = std::max(detailsLevel, 0);

    if(detailsLevel != oldLOD)
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, ibData[detailsLevel].size()*sizeof(GLuint),
            &ibData[detailsLevel][0], GL_STATIC_DRAW);
    }
}

int Detailing::getStep()
{
    return detailsSteps[detailsLevel];
}

GLuint Detailing::getVertexBuffer()
{
    return vertexBuffer;
}

GLuint Detailing::getIndexBuffer()
{
    return indexBuffer;
}
