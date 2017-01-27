#include "Area.hpp"

using namespace glm;

Area::Area(const char * filename) :
    geoCoeffs{vec2(0.0f, 0.0f)}
{
    countCoefficients(filename);
    readHeights(filename);

    glGenBuffers(1, &heightBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, heightBuffer);
    glBufferData(GL_ARRAY_BUFFER, hbData.size()*sizeof(GLfloat), &hbData[0], GL_STATIC_DRAW);
}

void Area::draw(GLuint pID, mat4 worldToCamera, Detailing * details, int dims)
{
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, details->getVertexBuffer());
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void *)0);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, heightBuffer);
    glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 0, (void *)0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, details->getIndexBuffer());

    GLint worldToCameraMat = glGetUniformLocation(pID, "worldToCameraMat");
    GLint longitudeFloat = glGetUniformLocation(pID, "longitude");
    GLint latitudeFloat = glGetUniformLocation(pID, "latitude");
    GLint mercatorFloat = glGetUniformLocation(pID, "mercator");
    GLint dimensionsInt = glGetUniformLocation(pID, "dimensions");

    glUniformMatrix4fv(worldToCameraMat, 1, GL_FALSE, &worldToCamera[0][0]);
    glUniform1f(longitudeFloat, geoCoeffs[0]);
    glUniform1f(latitudeFloat, geoCoeffs[1]);
    glUniform1f(mercatorFloat, MERCATOR);
    glUniform1i(dimensionsInt, dims);

    int indexSize = (SIDE-1)/details->getStep()+1;

    for(int i = 0; i < indexSize-1; ++i)
    {
        int ix = i*2*indexSize*sizeof(GLuint);

        glDrawElements(GL_TRIANGLE_STRIP, 2*indexSize, GL_UNSIGNED_INT, (void*)ix);
    }

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

std::pair<vec4, vec4> Area::getCorners(int dims)
{
    vec4 leftdown, rightup;

    if(dims == 2)
    {
        leftdown = vec4(countMapPosX(geoCoeffs[0]), countMapPosY(geoCoeffs[1]), 0.0f, 1.0f);
        rightup = vec4(countMapPosX(geoCoeffs[0]+1), countMapPosY(geoCoeffs[1]+1), 0.0f, 1.0f);
    }
    else
    {
        leftdown = vec4(countEarthPosX(geoCoeffs[0], geoCoeffs[1]), countEarthPosY(geoCoeffs[1]),
                        countEarthPosZ(geoCoeffs[0], geoCoeffs[1]), 1.0f);
        rightup = vec4(countEarthPosX(geoCoeffs[0]+1, geoCoeffs[1]+1),
                       countEarthPosY(geoCoeffs[1]+1),
                       countEarthPosZ(geoCoeffs[0]+1, geoCoeffs[1]+1), 1.0f);
    }

    return std::make_pair(leftdown, rightup);
}

GLfloat Area::countMapPosX(GLfloat longitude)
{
    return MERCATOR*radians(longitude);
}

GLfloat Area::countMapPosY(GLfloat latitude)
{
    return MERCATOR*log( tan(PI_CONST/4+radians(latitude)/2) );
}

GLfloat Area::countEarthPosX(GLfloat longitude, GLfloat latitude)
{
    return RADIUS*cos( radians(latitude) )*sin( radians(longitude) );
}

GLfloat Area::countEarthPosY(GLfloat latitude)
{
    return RADIUS*sin( radians(latitude) );
}

GLfloat Area::countEarthPosZ(GLfloat longitude, GLfloat latitude)
{
    return RADIUS*cos( radians(latitude) )*cos( radians(longitude) );
}

void Area::countCoefficients(const char * filename)
{
    auto digit = [](char c)
        {
            return +c-'0';
        };

    char latdir = filename[0];
    char lngdir = filename[3];

    short latval = digit(filename[1])*10+digit(filename[2]);
    short lngval = digit(filename[4])*100+digit(filename[5])*10+digit(filename[6]);

    switch(latdir)
    {
        case 'N':
        case 'n':
            geoCoeffs[1] = (GLfloat)latval;
            break;

        case 'S':
        case 's':
            geoCoeffs[1] = -(GLfloat)latval;
            break;
    }

    switch(lngdir)
    {
        case 'E':
        case 'e':
            geoCoeffs[0] = (GLfloat)lngval;
            break;

        case 'W':
        case 'w':
            geoCoeffs[0] = -(GLfloat)lngval;
            break;
    }
}

void Area::readHeights(const char * filename)
{
    FILE * file = fopen(filename, "r");

    while(true)
    {
        GLshort b1 = fgetc(file);

        if(b1 == EOF)
            break;

        GLshort b2 = fgetc(file);

        if(b2 == EOF)
            break;

        GLshort height = (b1<<8)|b2;

        hbData.push_back( (GLfloat)height );
    }

    fclose(file);
}
