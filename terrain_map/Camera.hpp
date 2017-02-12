#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <cstdlib>
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Area.hpp"
#include "Detailing.hpp"
#include "Earth.hpp"

using namespace glm;

class Camera
{
    private:
    static constexpr GLfloat PI_CONST = M_PI;
    static constexpr GLfloat MERCATOR = 360.0f/(2*PI_CONST);
    static constexpr GLfloat RADIUS = 6400000.0f;

    mat4 sc;
    mat4 view;
    mat4 proj;
    GLfloat distance;
    vec2 cameraCoeffs;
    vec2 cameraMapPos;
    vec3 cameraEarthPos;
    GLfloat fov;
    GLfloat persBegin;
    GLfloat persLength;
    int windowW;
    int windowH;

    public:
    int dims;

    Camera(GLFWwindow * window) :
        sc{mat4( vec4(1.0f, 0.0f, 0.0f, 0.0f),
                 vec4(0.0f, 1.0f, 0.0f, 0.0f),
                 vec4(0.0f, 0.0f, 1.0f, 0.0f),
                 vec4(0.0f, 0.0f, 0.0f, 1.0f) )},
        distance{1.005f*RADIUS},
        cameraCoeffs{vec2(0.0f, 0.0f)},
        cameraMapPos{vec2(0.0f, 0.0f)},
        cameraEarthPos{vec3(0.0f, 0.0f, distance)},
        fov{PI_CONST/3},
        persBegin{0.0025f*RADIUS},
        persLength{0.1f*RADIUS},
        dims{2}
    {
        glfwGetWindowSize(window, &windowW, &windowH);
        view = lookAt( vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, -1.0f), vec3(0.0f, 1.0f, 0.0f) );
        proj = perspective(fov, (1.0f*windowW)/windowH, persBegin, persLength);
    }

    int getDims();
    void changeDims();
    void drawEarth(GLuint pID, Earth * earth);
    void drawTerrain(GLuint pID, const std::vector<Area *> & areas, Detailing * details);
    long long int getTriangles(const std::vector<Area *> & areas, Detailing * details);
    vec2 getGeoCenter();
    GLfloat getZoom();
    void viewScale(GLfloat zoom);
    void resetScale();
    void viewRotate(GLfloat angleDeg, bool latitudeAlong);
    void cameraRotate(GLfloat angleDeg);
    void viewTranslate(vec3 trans);
    std::vector <bool> checkKeyPress(GLFWwindow * window, std::vector <int> & keys);

    private:
    vec3 cameraDir3D();
    bool areaInside(Area * area, mat4 scview);
};

#endif

