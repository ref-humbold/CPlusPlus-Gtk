#ifndef EARTH_HPP
#define EARTH_HPP

#include <cstdlib>
#include <iostream>
#include <cmath>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

using namespace glm;

class Earth
{
    private:
    std::vector<GLfloat> vbData;
    std::vector<GLuint> ibData;
    GLuint vertexBuffer;
    GLuint indexBuffer;

    int numLongs;
    int numLats;

    public:
    Earth();

    void draw(GLuint pID, mat4 worldToCamera);
};

#endif
