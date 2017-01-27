#ifndef GAME_CONTROLLER_HPP
#define GAME_CONTROLLER_HPP

#include <cstdlib>
#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

using namespace glm;

class GameController
{
    private:
    const GLfloat vbData[34];
    GLuint vertexBuffer;
    std::pair <int, int> size;
    std::vector <int> colorCodes;
    std::vector <int> signCodes;
    std::vector < std::pair <int, int> > transforms;
    std::vector <bool> visible;

    public:
    GameController(const std::pair <int, int> & size, int numColors, int numSigns);

    bool isVisible(int i);
    void setVisible(int i);
    void drawGame(GLuint pID, const std::pair <int, int> & pos, bool isCurVisible);
    int checkKeyPress(GLFWwindow * window);
    void checkKeyRelease(GLFWwindow * window, int key);
    int moveFrame(int key, int cur);
    bool checkSame(int prev, int cur);

    private:
    void drawSquares(GLuint pID, int col, std::pair <int, int> tr, int frameOffset);
    void drawSign(GLuint pID, int i);
};

#endif

