#ifndef GAME_BUBBLE_HPP
#define GAME_BUBBLE_HPP

#include <cstdlib>
#include <iostream>
#include <cmath>
#include <tuple>
#include <vector>
#include <list>
#include <algorithm>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

using namespace glm;

class GameBubble
{
    private:
    const GLfloat vbDataBubble[728];
    GLfloat cbDataBubble[728];
    GLfloat nbDataBubble[728];
    const GLushort ibDataBubble[380];
    GLuint vertexBufferBubble;
    GLuint colorBufferBubble;
    GLuint normalBufferBubble;
    GLuint indexBufferBubble;

    mat4 sc;
    mat4 rt;
    mat4 tr;
    GLfloat velocity;
    std::vector <vec3> coloring;

    public:
    int countElems;
    std::tuple <GLfloat, vec3, vec3> endGameBubble;
    std::list < std::tuple <GLfloat, vec3, vec3, int> > elements;

    GameBubble() :
        vbDataBubble{0.0f,          1.0f,           0.0f, 1.0f,             //0
                     0.309017f,     0.9510565,      0.0f, 1.0f,             //1
                     0.2938926f,    0.9510565f,     -0.0954915f, 1.0f,
                     0.25f ,        0.9510565f,     -0.18163563f, 1.0f,
                     0.18163563f,   0.9510565f,     -0.25f, 1.0f,
                     0.0954915f,    0.9510565f,     -0.29389262f, 1.0f,
                     0.0f,          0.9510565f,     -0.309017f, 1.0f,
                     -0.0954915f,   0.9510565f,     -0.2938926f, 1.0f,
                     -0.18163563f,  0.9510565f,     -0.25f, 1.0f,
                     -0.25f,        0.9510565f,     -0.18163563f, 1.0f,
                     -0.2938926f,   0.9510565f,     -0.0954915f, 1.0f,
                     -0.309017f,    0.9510565f,     0.0f , 1.0f,
                     -0.2938926f,   0.9510565f,     0.0954915f, 1.0f,
                     -0.25f,        0.9510565f,     0.18163563f, 1.0f,
                     -0.18163563f,  0.9510565f,     0.25f, 1.0f,
                     -0.0954915f,   0.9510565f,     0.2938926f, 1.0f,
                     0.0f,          0.9510565f,     0.309017f, 1.0f,
                     0.0954915f,    0.9510565f,     0.2938926f, 1.0f,
                     0.18163563f,   0.9510565f,     0.25f ,1.0f,
                     0.25f,         0.9510565f,     0.18163563f, 1.0f,
                     0.2938926f,    0.9510565f,     0.0954915f, 1.0f,
                     0.587785f,     0.809017f,      0.0f, 1.0f,             //21
                     0.559017f,     0.809017f,      -0.18163563f, 1.0f,
                     0.475528f,     0.809017f,      -0.3454915f, 1.0f,
                     0.3454915f,    0.809017f,      -0.47552826f, 1.0f,
                     0.18163563f,   0.809017f,      -0.559017f, 1.0f,
                     0.0f,          0.809017f,      -0.587785f, 1.0f,
                     -0.18163563f,  0.809017f,      -0.559017f, 1.0f,
                     -0.3454915f,   0.809017f,      -0.47552826f, 1.0f,
                     -0.47552826f,  0.809017f,      -0.3454915f, 1.0f,
                     -0.559017f,    0.809017f,      -0.18163563f, 1.0f,
                     -0.58778525f,  0.809017f,      0.0f, 1.0f,
                     -0.559017f,    0.809017f,      0.18163563f, 1.0f,
                     -0.47552826f,  0.809017f,      0.3454915f, 1.0f,
                     -0.3454915f,   0.809017f,      0.47552826f, 1.0f,
                     -0.18163563f,  0.809017f,      0.559017f, 1.0f,
                     0.0f,          0.809017f,      0.58778525f, 1.0f,
                     0.18163563f,   0.809017f,      0.559017f, 1.0f,
                     0.3454915f,    0.809017f,      0.47552826f, 1.0f,
                     0.47552826f,   0.809017f,      0.3454915f, 1.0f,
                     0.559017f,     0.809017f,      0.18163563f, 1.0f,
                     0.809017f,     0.587785f,      0.0f, 1.0f,             //41
                     0.76942f,      0.587785f,      -0.25f, 1.0f,
                     0.6545085f,    0.587785f,      -0.47552826f, 1.0f,
                     0.47552826f,   0.587785f,      -0.6545085f, 1.0f,
                     0.25f,         0.587785f,      -0.76942f, 1.0f,
                     0.0f,          0.587785f,      -0.809017f, 1.0f,
                     -0.25f,        0.587785f,      -0.76942f, 1.0f,
                     -0.47552826f,  0.587785f,      -0.6545085f, 1.0f,
                     -0.6545085f,   0.587785f,      -0.47552826f, 1.0f,
                     -0.76942f,     0.587785f,      -0.25f, 1.0f,
                     -0.809017f,    0.587785f,      0.0f, 1.0f,
                     -0.76942f,     0.587785f,      0.25f, 1.0f,
                     -0.6545085f,   0.587785f,      0.47552826f, 1.0f,
                     -0.47552826f,  0.587785f,      0.6545085f, 1.0f,
                     -0.25f,        0.587785f,      0.76942f, 1.0f,
                     0.0f,          0.587785f,      0.809017f, 1.0f,
                     0.25f,         0.587785f,      0.76942f, 1.0f,
                     0.47552826f,   0.587785f,      0.6545085f, 1.0f,
                     0.6545085f,    0.587785f,      0.47552826f, 1.0f,
                     0.76942f,      0.587785f,      0.25f, 1.0f,
                     0.9510565,     0.309017f,      0.0f, 1.0f,             //61
                     0.9045085f,    0.309017f,      -0.2938926f, 1.0f,
                     0.7694209f,    0.309017f,      -0.559017f, 1.0f,
                     0.559017f,     0.309017f,      -0.7694209f, 1.0f,
                     0.2938926f,    0.309017f,      -0.9045085f, 1.0f,
                     0.0f,          0.309017f,      -0.9510565f, 1.0f,
                     -0.2938926f,   0.309017f,      -0.9045085f, 1.0f,
                     -0.559017f,    0.309017f,      -0.7694209f, 1.0f,
                     -0.7694209f,   0.309017f,      -0.559017f, 1.0f,
                     -0.9045085f,   0.309017f,      -0.2938926f, 1.0f,
                     -0.9510565f,   0.309017f,      0.0f, 1.0f,
                     -0.9045085f,   0.309017f,      0.2938926f, 1.0f,
                     -0.7694209f,   0.309017f,      0.559017f, 1.0f,
                     -0.559017f,    0.309017f,      0.7694209f, 1.0f,
                     -0.2938926f,   0.309017f,      0.9045085f, 1.0f,
                     0.0f,          0.309017f,      0.9510565f, 1.0f,
                     0.2938926f,    0.309017f,      0.9045085f, 1.0f,
                     0.559017f,     0.309017f,      0.7694209f, 1.0f,
                     0.7694209f,    0.309017f,      0.559017f, 1.0f,
                     0.9045085f,    0.309017f,      0.2938926f, 1.0f,
                     1.0f,          0.0f,           0.0f, 1.0f,             //81
                     0.9510565f,    0.0f,           -0.309017f, 1.0f,
                     0.809017f,     0.0f,           -0.58778525f, 1.0f,
                     0.58778525f,   0.0f,           -0.809017f, 1.0f,
                     0.309017f,     0.0f,           -0.9510565f, 1.0f,
                     0.0f,          0.0f,           -1.0, 1.0f,
                     -0.309017f,    0.0f,           -0.9510565f, 1.0f,
                     -0.58778525f,  0.0f,           -0.809017f, 1.0f,
                     -0.809017f,    0.0f,           -0.58778525f, 1.0f,
                     -0.9510565f,   0.0f,           -0.309017f, 1.0f,
                     -1.0,          0.0f,           0.0f, 1.0f,
                     -0.9510565f,   0.0f,           0.309017f, 1.0f,
                     -0.809017f,    0.0f,           0.58778525f, 1.0f,
                     -0.58778525f,  0.0f,           0.809017f, 1.0f,
                     -0.309017f,    0.0f,           0.9510565f, 1.0f,
                     0.0f,          0.0f,           1.0f, 1.0f,
                     0.309017f,     0.0f,           0.9510565f, 1.0f,
                     0.58778525f,   0.0f,           0.809017f, 1.0f,
                     0.809017f,     0.0f,           0.58778525f, 1.0f,
                     0.9510565f,    0.0f,           0.309017f, 1.0f,
                     0.9510565,     -0.309017f,     0.0f, 1.0f,             //101
                     0.9045085f,    -0.309017f,     -0.2938926f, 1.0f,
                     0.7694209f,    -0.309017f,     -0.559017f, 1.0f,
                     0.559017f,     -0.309017f,     -0.7694209f, 1.0f,
                     0.2938926f,    -0.309017f,     -0.9045085f, 1.0f,
                     0.0f,          -0.309017f,     -0.9510565f, 1.0f,
                     -0.2938926f,   -0.309017f,     -0.9045085f, 1.0f,
                     -0.559017f,    -0.309017f,     -0.7694209f, 1.0f,
                     -0.7694209f,   -0.309017f,     -0.559017f, 1.0f,
                     -0.9045085f,   -0.309017f,     -0.2938926f, 1.0f,
                     -0.9510565f,   -0.309017f,     0.0f, 1.0f,
                     -0.9045085f,   -0.309017f,     0.2938926f, 1.0f,
                     -0.7694209f,   -0.309017f,     0.559017f, 1.0f,
                     -0.559017f,    -0.309017f,     0.7694209f, 1.0f,
                     -0.2938926f,   -0.309017f,     0.9045085f, 1.0f,
                     0.0f,          -0.309017f,     0.9510565f, 1.0f,
                     0.2938926f,    -0.309017f,     0.9045085f, 1.0f,
                     0.559017f,     -0.309017f,     0.7694209f, 1.0f,
                     0.7694209f,    -0.309017f,     0.559017f, 1.0f,
                     0.9045085f,    -0.309017f,     0.2938926f, 1.0f,
                     0.809017f,     -0.587785f,     0.0f, 1.0f,             //121
                     0.76942f,      -0.587785f,     -0.25f, 1.0f,
                     0.6545085f,    -0.587785f,     -0.47552826f, 1.0f,
                     0.47552826f,   -0.587785f,     -0.6545085f, 1.0f,
                     0.25f,         -0.587785f,     -0.76942f, 1.0f,
                     0.0f,          -0.587785f,     -0.809017f, 1.0f,
                     -0.25f,        -0.587785f,     -0.76942f, 1.0f,
                     -0.47552826f,  -0.587785f,     -0.6545085f, 1.0f,
                     -0.6545085f,   -0.587785f,     -0.47552826f, 1.0f,
                     -0.76942f,     -0.587785f,     -0.25f, 1.0f,
                     -0.809017f,    -0.587785f,     0.0f, 1.0f,
                     -0.76942f,     -0.587785f,     0.25f, 1.0f,
                     -0.6545085f,   -0.587785f,     0.47552826f, 1.0f,
                     -0.47552826f,  -0.587785f,     0.6545085f, 1.0f,
                     -0.25f,        -0.587785f,     0.76942f, 1.0f,
                     0.0f,          -0.587785f,     0.809017f, 1.0f,
                     0.25f,         -0.587785f,     0.76942f, 1.0f,
                     0.47552826f,   -0.587785f,     0.6545085f, 1.0f,
                     0.6545085f,    -0.587785f,     0.47552826f, 1.0f,
                     0.76942f,      -0.587785f,     0.25f, 1.0f,
                     0.587785f,     -0.809017f,     0.0f, 1.0f,             //141
                     0.559017f,     -0.809017f,     -0.18163563f, 1.0f,
                     0.475528f,     -0.809017f,     -0.3454915f, 1.0f,
                     0.3454915f,    -0.809017f,     -0.47552826f, 1.0f,
                     0.18163563f,   -0.809017f,     -0.559017f, 1.0f,
                     0.0f,          -0.809017f,     -0.587785f, 1.0f,
                     -0.18163563f,  -0.809017f,     -0.559017f, 1.0f,
                     -0.3454915f,   -0.809017f,     -0.47552826f, 1.0f,
                     -0.47552826f,  -0.809017f,     -0.3454915f, 1.0f,
                     -0.559017f,    -0.809017f,     -0.18163563f, 1.0f,
                     -0.58778525f,  -0.809017f,     0.0f, 1.0f,
                     -0.559017f,    -0.809017f,     0.18163563f, 1.0f,
                     -0.47552826f,  -0.809017f,     0.3454915f, 1.0f,
                     -0.3454915f,   -0.809017f,     0.47552826f, 1.0f,
                     -0.18163563f,  -0.809017f,     0.559017f, 1.0f,
                     0.0f,          -0.809017f,     0.58778525f, 1.0f,
                     0.18163563f,   -0.809017f,     0.559017f, 1.0f,
                     0.3454915f,    -0.809017f,     0.47552826f, 1.0f,
                     0.47552826f,   -0.809017f,     0.3454915f, 1.0f,
                     0.559017f,     -0.809017f,     0.18163563f, 1.0f,
                     0.309017f,     -0.9510565,     0.0f, 1.0f,             //161
                     0.2938926f,    -0.9510565f,    -0.0954915f, 1.0f,
                     0.25f ,        -0.9510565f,    -0.18163563f, 1.0f,
                     0.18163563f,   -0.9510565f,    -0.25f, 1.0f,
                     0.0954915f,    -0.9510565f,    -0.29389262f, 1.0f,
                     0.0f,          -0.9510565f,    -0.309017f, 1.0f,
                     -0.0954915f,   -0.9510565f,    -0.2938926f, 1.0f,
                     -0.18163563f,  -0.9510565f,    -0.25f, 1.0f,
                     -0.25f,        -0.9510565f,    -0.18163563f, 1.0f,
                     -0.2938926f,   -0.9510565f,    -0.0954915f, 1.0f,
                     -0.309017f,    -0.9510565f,    0.0f , 1.0f,
                     -0.2938926f,   -0.9510565f,    0.0954915f, 1.0f,
                     -0.25f,        -0.9510565f,    0.18163563f, 1.0f,
                     -0.18163563f,  -0.9510565f,    0.25f, 1.0f,
                     -0.0954915f,   -0.9510565f,    0.2938926f, 1.0f,
                     0.0f,          -0.9510565f,    0.309017f, 1.0f,
                     0.0954915f,    -0.9510565f,    0.2938926f, 1.0f,
                     0.18163563f,   -0.9510565f,    0.25f ,1.0f,
                     0.25f,         -0.9510565f,    0.18163563f, 1.0f,
                     0.2938926f,    -0.9510565f,    0.0954915f, 1.0f,
                     0.0f,          -1.0f,          0.0f, 1.0f},            //181
        cbDataBubble{1.0f, 1.0f, 1.0f, 1.0f,  //0
                     1.0f, 1.0f, 1.0f, 1.0f,  //1
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,  //21
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,  //41
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,  //61
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,  //81
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,  //101
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,  //121
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,  //141
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,  //161
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f, 1.0f},  //181
        nbDataBubble{0.0f, 0.0f, 0.0f, 0.0f,  //0
                     0.0f, 0.0f, 0.0f, 0.0f,  //1
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,  //21
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,  //41
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,  //61
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,  //81
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,  //101
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,  //121
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,  //141
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,  //161
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, 0.0f, 0.0f},  //181
        ibDataBubble{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 1,  //0
                     1, 21, 2, 22, 3, 23, 4, 24, 5, 25, 6, 26, 7, 27, 8, 28, 9, 29, 10, 30,  //22
                     11, 31, 12, 32, 13, 33, 14, 34, 15, 35, 16, 36, 17, 37, 18, 38, 19, 39, 20, 40,
                     1, 21,
                     21, 41, 22, 42, 23, 43, 24, 44, 25, 45, 26, 46, 27, 47, 28, 48, 29, 49, 30, 50,  //64
                     31, 51, 32, 52, 33, 53, 34, 54, 35, 55, 36, 56, 37, 57, 38, 58, 39, 59, 40, 60,
                     21, 41,
                     41, 61, 42, 62, 43, 63, 44, 64, 45, 65, 46, 66, 47, 67, 48, 68, 49, 69, 50, 70,  //106
                     51, 71, 52, 72, 53, 73, 54, 74, 55, 75, 56, 76, 57, 77, 58, 78, 59, 79, 60, 80,
                     41, 61,
                     61, 81, 62, 82, 63, 83, 64, 84, 65, 85, 66, 86, 67, 87, 68, 88, 69, 89, 70, 90,  //148
                     71, 91, 72, 92, 73, 93, 74, 94, 75, 95, 76, 96, 77, 97, 78, 98, 79, 99, 80, 100,
                     61, 81,
                     81, 101, 82, 102, 83, 103, 84, 104, 85, 105, 86, 106, 87, 107, 88, 108, 89, 109, 90, 110,  //190
                     91, 111, 92, 112, 93, 113, 94, 114, 95, 115, 96, 116, 97, 117, 98, 118, 99, 119, 100, 120,
                     81, 101,
                     101, 121, 102, 122, 103, 123, 104, 124, 105, 125, 106, 126, 107, 127, 108, 128, 109, 129, 110, 130,  //232
                     111, 131, 112, 132, 113, 133, 114, 134, 115, 135, 116, 136, 117, 137, 118, 138, 119, 139, 120, 140,
                     101, 121,
                     121, 141, 122, 142, 123, 143, 124, 144, 125, 145, 126, 146, 127, 147, 128, 148, 129, 149, 130, 150,  //274
                     131, 151, 132, 152, 133, 153, 134, 154, 135, 155, 136, 156, 137, 157, 138, 158, 139, 159, 140, 160,
                     121, 141,
                     141, 161, 142, 162, 143, 163, 144, 164, 145, 165, 146, 166, 147, 167, 148, 168, 149, 169, 150, 170,  //316
                     151, 171, 152, 172, 153, 173, 154, 174, 155, 175, 156, 176, 157, 177, 158, 178, 159, 179, 160, 180,
                     141, 161,
                     181, 180, 179, 178, 177, 176, 175, 174, 173, 172, 171, 170, 169, 168, 167, 166, 165, 164, 163, 162, 161, 180},  //358
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
                 vec4(0.0f, 0.0f, 0.0f, 1.0f) )},
        velocity{0.5f},
        coloring{vec3(0.5f, 0.0f, 0.0f),
                 vec3(0.6f, 0.0f, 0.0f),
                 vec3(0.7f, 0.0f, 0.0f),
                 vec3(0.8f, 0.0f, 0.0f),
                 vec3(0.9f, 0.0f, 0.0f),
                 vec3(1.0f, 0.0f, 0.0f),
                 vec3(0.0f, 0.5f, 0.0f),
                 vec3(0.0f, 0.6f, 0.0f),
                 vec3(0.0f, 0.7f, 0.0f),
                 vec3(0.0f, 0.8f, 0.0f),
                 vec3(0.0f, 0.9f, 0.0f),
                 vec3(0.0f, 1.0f, 0.0f),
                 vec3(0.5f, 0.5f, 0.0f),
                 vec3(0.6f, 0.6f, 0.0f),
                 vec3(0.7f, 0.7f, 0.0f),
                 vec3(0.8f, 0.8f, 0.0f),
                 vec3(0.9f, 0.9f, 0.0f),
                 vec3(1.0f, 1.0f, 0.0f),
                 vec3(0.5f, 0.0f, 0.5f),
                 vec3(0.6f, 0.0f, 0.6f),
                 vec3(0.7f, 0.0f, 0.7f),
                 vec3(0.8f, 0.0f, 0.8f),
                 vec3(0.9f, 0.0f, 0.9f),
                 vec3(1.0f, 0.0f, 1.0f),
                 vec3(0.0f, 0.5f, 0.5f),
                 vec3(0.0f, 0.6f, 0.6f),
                 vec3(0.0f, 0.7f, 0.7f),
                 vec3(0.0f, 0.8f, 0.8f),
                 vec3(0.0f, 0.9f, 0.9f),
                 vec3(0.0f, 1.0f, 1.0f)},
        countElems{1}
    {
        countNormals();
        endGameBubble = std::make_tuple( 0.025f, vec3(-0.475, -0.475, -0.475),
            vec3(0.0f, 0.0f, 0.0f) );

        glGenBuffers(1, &vertexBufferBubble);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferBubble);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vbDataBubble), vbDataBubble, GL_STATIC_DRAW);

        glGenBuffers(1, &colorBufferBubble);
        glBindBuffer(GL_ARRAY_BUFFER, colorBufferBubble);
        glBufferData(GL_ARRAY_BUFFER, sizeof(cbDataBubble), cbDataBubble, GL_STATIC_DRAW);

        glGenBuffers(1, &normalBufferBubble);
        glBindBuffer(GL_ARRAY_BUFFER, normalBufferBubble);
        glBufferData(GL_ARRAY_BUFFER, sizeof(nbDataBubble), nbDataBubble, GL_STATIC_DRAW);

        glGenBuffers(1, &indexBufferBubble);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferBubble);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ibDataBubble), ibDataBubble, GL_STATIC_DRAW);
    }

    void drawAllBubbles(GLuint pID, mat4 worldToCamera, mat4 cameraToClip,
        vec4 lightSource);
    void drawBubble(GLuint pID, mat4 worldToCamera, mat4 cameraToClip,
        vec4 lightSource, GLfloat radius, vec3 position);
    void setColor(vec3 color);
    void showUp(GLfloat side);
    void move(GLfloat delta, GLfloat side);
    vec3 normalVec(GLushort i1, GLushort i2, GLushort i3);
    void countNormals();
};

#endif

