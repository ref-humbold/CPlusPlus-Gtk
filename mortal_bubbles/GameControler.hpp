#ifndef GAME_CONTROLER_HPP
#define GAME_CONTROLER_HPP

#include <cstdlib>
#include <iostream>
#include <cmath>
#include <tuple>
#include <vector>
#include <algorithm>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include "GameAquarium.hpp"
#include "GameBubble.hpp"
#include "GamePlayer.hpp"

using namespace glm;

class GameControler
{
    private:
    static constexpr GLfloat PI_CONST = M_PI;

    GameAquarium * aqua;
    GamePlayer * player;
    GameBubble * bubble;

    mat4 view;
    mat4 proj;
    vec3 cameraPos;
    vec3 cameraDir;
    std::vector<vec4> playerMoves;
    bool viewInside;
    GLfloat fov;
    GLfloat persBegin;
    GLfloat persStep;
    vec4 lightSource;
    int windowW;
    int windowH;

    public:
    double points;

    GameControler(GLFWwindow * window) :
        aqua{new GameAquarium()},
        player{new GamePlayer()},
        bubble{new GameBubble()},
        cameraPos{vec3(0.0f, 0.0f, 3.0f)},
        cameraDir{vec3(0.0f, 0.0f, 0.0f)},
        viewInside{false},
        fov{PI_CONST/4},
        persBegin{1.0f},
        persStep{4.0f},
        points{1.0}
    {
        playerMoves.push_back( vec4(0.0f, 0.0f, -1.0f, 0.0f) ); //W
        playerMoves.push_back( vec4(0.0f, 0.0f, 1.0f, 0.0f) );  //X
        playerMoves.push_back( vec4(0.0f, 1.0f, 0.0f, 0.0f) );  //E
        playerMoves.push_back( vec4(0.0f, -1.0f, 0.0f, 0.0f) ); //Z
        playerMoves.push_back( vec4(-1.0f, 0.0f, 0.0f, 0.0f) ); //A
        playerMoves.push_back( vec4(1.0f, 0.0f, 0.0f, 0.0f) );  //D

        lightSource = vec4(0.0f, aqua->getSide(), 0.0f, 1.0f);

        glfwGetWindowSize(window, &windowW, &windowH);
        view = lookAt( cameraPos, cameraDir, vec3(0.0f, 1.0f, 0.0f) );
        proj = perspective(fov, (1.0f*windowW)/windowH, persBegin, persBegin+persStep);
    }

    ~GameControler()
    {
        delete aqua;
        delete player;
        delete bubble;
    }

    void drawGame(GLuint pID);
    void restart();
    void restartMoves();
    void setCamera();
    void changeCamera();
    void viewScale(GLfloat zoom);
    void viewRotate(GLfloat angleRad, vec3 axis);
    int checkCollisionBubble();
    bool checkEndRound();
    void deletePointedBubble(int ix);
    GLfloat moveBubbles(GLfloat delta, GLfloat counter, int freq);
    void movePlayer(GLfloat delta, std::vector<bool> movesMask);
    vec3 getMousePos(GLFWwindow * window);
    std::vector<bool> checkKeyPress(GLFWwindow * window, std::vector<int> & keys);
    bool checkMouseAction(GLFWwindow * window, int action);
    void checkTabReleased(GLFWwindow * window);
};

#endif
