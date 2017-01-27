#ifndef GAME_ELEMENT_HPP
#define GAME_ELEMENT_HPP

#include <cstdlib>
#include <iostream>
#include <cmath>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

using namespace glm;

GLuint createVertexBuffer(const GLfloat vbData[], size_t size);

void loadBuffer(GLuint vb, GLuint cb);

class GameBoard
{
    private:
    const GLfloat vbDataHexagon[16];
    const GLfloat cbDataHexagon[24];
    const GLfloat vbDataTriangle[6];
    const GLfloat cbDataTriangle[9];
    GLuint vertexBufferHexagon;
    GLuint colorBufferHexagon;
    GLuint vertexBufferTriangle;
    GLuint colorBufferTriangle;

    mat2 sc;
    mat2 rt;
    vec2 tr;

    public:
    std::vector <vec2> normVecs;

    GameBoard() :
        vbDataHexagon{0.0f, 0.0f,
                      0.4f, 0.0f,
                      0.2f, 0.34641f,
                      -0.2f, 0.34641f,
                      -0.4f, 0.0f,
                      -0.2f, -0.34641f,
                      0.2f, -0.34641f,
                      0.4f, 0.0f},
        cbDataHexagon{0.0f, 0.6f, 0.6f,
                      0.0f, 0.0f, 0.25f,
                      0.0f, 0.0f, 0.25f,
                      0.0f, 0.0f, 0.25f,
                      0.0f, 0.0f, 0.25f,
                      0.0f, 0.0f, 0.25f,
                      0.0f, 0.0f, 0.25f,
                      0.0f, 0.0f, 0.25f},
        vbDataTriangle{0.0f, 0.0f,
                       0.0f, 1.0f,
                       0.57735f, 0.0f},
        cbDataTriangle{0.0f, 0.0f, 0.0f,
                       0.0f, 0.0f, 0.0f,
                       0.0f, 0.0f, 0.0f},
        sc{mat2( vec2(1.0f, 0.0f), vec2(0.0f, 1.0f) )},
        rt{mat2( vec2(1.0f, 0.0f), vec2(0.0f, 1.0f) )},
        tr{vec2(0.0f, 0.0f)}
    {
        vertexBufferHexagon = createVertexBuffer( vbDataHexagon, sizeof(vbDataHexagon) );
        colorBufferHexagon = createVertexBuffer( cbDataHexagon, sizeof(cbDataHexagon) );
        vertexBufferTriangle = createVertexBuffer( vbDataTriangle, sizeof(vbDataTriangle) );
        colorBufferTriangle = createVertexBuffer( cbDataTriangle, sizeof(cbDataTriangle) );
        normVecs.resize(5);
    }

    void drawBackground(GLuint pID);
    void drawBorderTriangles(GLuint pID);
    void countNormalVectors();

    private:
    void drawOneTriangle(GLuint pID);
};

class GameBrick
{
    private:
    const GLfloat vbDataRect[8];
    GLfloat cbDataRect[12];
    const GLfloat cbDataRectBorder[12];
    GLuint vertexBufferRect;
    GLuint colorBufferRect;
    GLuint colorBufferRectBorder;

    mat2 sc;
    mat2 rt;
    vec2 tr;
    bool modeHard;

    public:
    std::vector < std::vector <bool> > isVisible;
    int bricksLeft;

    GameBrick(bool modeHard) :
        vbDataRect{0.5f, 0.25f,
                   0.5f, -0.25f,
                   -0.5f, -0.25f,
                   -0.5f, 0.25f},
        cbDataRect{1.0f, 1.0f, 1.0f,
                   1.0f, 1.0f, 1.0f,
                   1.0f, 1.0f, 1.0f,
                   1.0f, 1.0f, 1.0f},
        cbDataRectBorder{0.0f, 0.0f, 0.0f,
                         0.0f, 0.0f, 0.0f,
                         0.0f, 0.0f, 0.0f,
                         0.0f, 0.0f, 0.0f},
        sc{mat2( vec2(0.1f, 0.0f), vec2(0.0f, 0.1f) )},
        rt{mat2( vec2(1.0f, 0.0f), vec2(0.0f, 1.0f) )},
        tr{vec2(0.0f, 0.0f)},
        modeHard{modeHard}
    {
        vertexBufferRect = createVertexBuffer( vbDataRect, sizeof(vbDataRect) );
        colorBufferRect = createVertexBuffer( cbDataRect, sizeof(cbDataRect) );
        colorBufferRectBorder = createVertexBuffer( cbDataRectBorder, sizeof(cbDataRectBorder) );

        if(modeHard)
        {
            bricksLeft = 74;
            isVisible.resize(6);

            for(auto & vc : isVisible)
                vc.resize(13, true);

            isVisible[4][0] = false;
            isVisible[4][12] = false;
            isVisible[5][0] = false;
            isVisible[5][12] = false;
        }
        else
        {
            bricksLeft = 13;
            isVisible.resize(1);
            isVisible[0].resize(13, true);
        }
    }

    void drawAllBricks(GLuint pID);

    private:
    void drawRect(GLuint pID, int col);
    void drawRectBorder(GLuint pID);
};

class GamePaddle
{
    private:
    const GLfloat vbDataPaddle[20];
    const GLfloat cbDataPaddle[30];
    GLuint vertexBufferPaddle;
    GLuint colorBufferPaddle;

    mat2 sc;
    mat2 rt;
    vec2 tr;
    GLfloat velocity;

    public:
    GamePaddle() :
        vbDataPaddle{0.0f, 0.0f,
                     0.4f, -0.05f,
                     0.6f, 0.1f,
                     -0.6f, 0.1f,
                     -0.4f, -0.05f},
        cbDataPaddle{1.0f, 1.0f, 1.0f,
                     0.8f, 0.8f, 0.8f,
                     0.2f, 0.2f, 0.2f,
                     0.2f, 0.2f, 0.2f,
                     0.8f, 0.8f, 0.8f},
        sc{mat2( vec2(0.1f, 0.0f), vec2(0.0f, 0.1f) )},
        rt{mat2( vec2(1.0f, 0.0f), vec2(0.0f, 1.0f) )},
        tr{vec2(0.0f, -0.95f)},
        velocity{1.0f}
    {
        vertexBufferPaddle = createVertexBuffer( vbDataPaddle, sizeof(vbDataPaddle) );
        colorBufferPaddle = createVertexBuffer( cbDataPaddle, sizeof(cbDataPaddle) );
    }

    void restart();
    void drawPaddle(GLuint pID);
    void moveLeft(GLfloat delta);
    void moveRight(GLfloat delta);
    GLfloat getPosX();
    GLfloat getSurf();
};

class GameBall
{
    private:
    const GLfloat vbDataBall[28];
    const GLfloat cbDataBall[42];
    const GLfloat vbDataCross[8];
    const GLfloat cbDataCross[12];
    GLuint vertexBufferBall;
    GLuint colorBufferBall;
    GLuint vertexBufferCross;
    GLuint colorBufferCross;

    mat2 sc;
    mat2 rt;
    vec2 tr;
    vec2 velocity;
    vec2 vNorm;
    int angleMult;
    GLfloat radius;
    GLfloat separator;
    GLfloat velDist;
    bool startingShot;
    std::vector < std::vector < std::pair <bool, bool> > > collided;

    public:
    GameBall() :
        vbDataBall{0.0f, 0.0f,
                   0.05f, 0.18660254f,
                   0.13660254f, 0.13660254f,
                   0.18660254f, 0.05f,
                   0.18660254f, -0.05f,
                   0.13660254f, -0.13660254f,
                   0.05f, -0.18660254f,
                   -0.05f, -0.18660254f,
                   -0.13660254f, -0.13660254f,
                   -0.18660254f, -0.05f,
                   -0.18660254f, 0.05f,
                   -0.13660254f, 0.13660254f,
                   -0.05f, 0.18660254f,
                   0.05f, 0.18660254f},
        cbDataBall{0.8f, 0.8f, 0.8f,
                   0.35f, 0.35f, 0.35f,
                   0.35f, 0.35f, 0.35f,
                   0.35f, 0.35f, 0.35f,
                   0.35f, 0.35f, 0.35f,
                   0.35f, 0.35f, 0.35f,
                   0.35f, 0.35f, 0.35f,
                   0.35f, 0.35f, 0.35f,
                   0.35f, 0.35f, 0.35f,
                   0.35f, 0.35f, 0.35f,
                   0.35f, 0.35f, 0.35f,
                   0.35f, 0.35f, 0.35f,
                   0.35f, 0.35f, 0.35f,
                   0.35f, 0.35f, 0.35f},
        vbDataCross{0.13660254f, 0.13660254f,
                    -0.13660254f, -0.13660254f,
                    0.13660254f, -0.13660254f,
                    -0.13660254f, 0.13660254f},
        cbDataCross{0.0f, 0.0f, 0.0f,
                    0.0f, 0.0f, 0.0f,
                    0.0f, 0.0f, 0.0f,
                    0.0f, 0.0f, 0.0f},
        sc{mat2( vec2(0.08f, 0.0f), vec2(0.0f, 0.08f) )},
        rt{mat2( vec2(1.0f, 0.0f), vec2(0.0f, 1.0f) )},
        tr{vec2(0.0f, -0.9f)},
        vNorm{vec2(0.0f, 0.0f)},
        angleMult{0},
        radius{length( sc*vec2(0.13660254f, 0.13660254f) )},
        separator{1.25f*radius},
        velDist{50.0f*radius},
        startingShot{true}
    {
        vertexBufferBall = createVertexBuffer( vbDataBall, sizeof(vbDataBall) );
        colorBufferBall = createVertexBuffer( cbDataBall, sizeof(cbDataBall) );
        vertexBufferCross = createVertexBuffer( vbDataCross, sizeof(vbDataCross) );
        colorBufferCross = createVertexBuffer( cbDataCross, sizeof(cbDataCross) );

        velocity = velDist*normalize( vec2( (-10.0f+rand()%21)/10.0f, 1.0f) );
        collided.resize(7);

        for(int i = 0; i < 5; ++i)
            collided[i].resize( 13, std::make_pair(false, false) );

        collided[5].resize( 5, std::make_pair(false, false) );
        collided[6].resize( 1, std::make_pair(false, false) );
    }

    void restart();
    void drawBall(GLuint pID);
    void drawCross(GLuint pID);
    bool isInRange(GLfloat value, GLfloat minR, GLfloat maxR);
    GLfloat countDistance(vec2 pt, vec2 nl, vec2 pl);
    bool checkOutside();
    void checkCollisionBoard(GameBoard * board);
    void checkCollisionPaddle(GamePaddle * paddle);
    void checkCollisionBrickHard(GameBrick * brick);
    void checkCollisionBrickEasy(GameBrick * brick);
    void moveBall(GLfloat delta);
};

class GameControler
{
    public:
    GameControler()
    {
    }

    void drawGame(GLuint pID, GameBoard * board, GameBall * ball, GameBrick * brick, GamePaddle * paddle);
    int checkKeyPress(GLFWwindow * window);
    void checkKeyRelease(GLFWwindow * window, int key);
};

#endif
