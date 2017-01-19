#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "GLSLloader.hpp"
#include "GameElement.hpp"

using namespace glm;

void glfwHints()
{
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

int main(int argc, char * argv[])
{
    bool modeHard = true;

    if(argc == 2)
    {
        std::string modeArg = argv[1];

        if(modeArg == "0" || modeArg == "E" || modeArg == "e")
            modeHard = false;
        else if(modeArg != "1" && modeArg != "H" && modeArg == "h")
        {
            fprintf(stderr, "BŁĄD! NIEPOPRAWNY ARGUMENT.\n");
            return -1;
        }
    }
    else if(argc >= 3)
    {
        fprintf(stderr, "BŁĄD! ZA DUŻO ARGUMENTÓW.\n");
        return -1;
    }

    // inicjalizacja OpenGL

    if(!glfwInit())
    {
        fprintf(stderr, "FAILED TO INITIALIZE GLFW\n");
        return -1;
    }

    glfwHints();

    GLFWwindow * window = glfwCreateWindow(1024, 768, "Arkanoid", NULL, NULL);

    if(window == NULL)
    {
        fprintf(stderr, "FAILED TO OPEN A NEW WINDOW\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glewExperimental = true;

    if(glewInit() != GLEW_OK)
    {
        fprintf(stderr, "FAILED TO INITIALIZE GLEW\n");
        return -1;
    }

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    GLuint programID = loadShaders("VertexShader.glsl", "FragmentShader.glsl");

    createVertexArray();

    // inicjalizacja elementów planszy

    srand( time(0) );

    GameControler * ctrl = new GameControler();
    GameBoard * board = new GameBoard();
    GameBall * ball = new GameBall();
    GameBrick * brick = new GameBrick(modeHard);
    GamePaddle * paddle = new GamePaddle();

    int gamePhase = 0, tryings = 0;
    GLfloat timer = 0.0f, pauseTime;

    // kontrola gry

    do
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(programID);

        ctrl->drawGame(programID, board, ball, brick, paddle);

        glfwSwapBuffers(window);
        glfwPollEvents();

        if(gamePhase == 1)
        {
            int keyCode = ctrl->checkKeyPress(window);

            switch(keyCode)
            {
                case 0:
                    pauseTime = glfwGetTime();
                    ctrl->checkKeyRelease(window, keyCode);
                    std::cout << "\tPRZERWA - wciśnij spację, by kontunuować grę\n";
                    gamePhase = 0;
                    break;

                case 1:
                    paddle->moveLeft(glfwGetTime()-timer);
                    break;

                case 2:
                    paddle->moveRight(glfwGetTime()-timer);
                    break;
            }

            if(ball->checkOutside())
            {
                std::cout << "KULKA SPADŁA Z PLANSZY!! Spróbuj ponownie.\n";
                gamePhase = 0;
                ++tryings;
                ball->restart();
                paddle->restart();
            }
            else
            {
                ball->checkCollisionPaddle(paddle);

                if(modeHard)
                    ball->checkCollisionBrickHard(brick);
                else
                    ball->checkCollisionBrickEasy(brick);

                ball->checkCollisionBoard(board);

                GLfloat delta = gamePhase == 0 ? pauseTime-timer : glfwGetTime()-timer;
                timer = glfwGetTime();

                ball->moveBall(delta);

                if(brick->bricksLeft == 0)
                {
                    std::cout << "WYGRAŁEŚ!! Kulka spadła Ci " << tryings << " razy.\n";
                    std::cout << "Wciśnij spację, by zakończyć.\n";
                    gamePhase = 2;
                }
            }
        }
        else
        {
            int keyCode = ctrl->checkKeyPress(window);

            if(keyCode == 0)
            {
                if(gamePhase == 2)
                    break;

                ctrl->checkKeyRelease(window, keyCode);
                gamePhase = 1;
                timer = glfwGetTime();
                std::cout << "\tGRAMY!!\n\n";
            }
        }
    }
    while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);

    if(brick->bricksLeft != 0)
        std::cout << "PRZERWANO GRĘ\n\n";

    glfwTerminate();
    delete ctrl;
    delete board;
    delete ball;
    delete brick;
    delete paddle;

    return 0;
}

