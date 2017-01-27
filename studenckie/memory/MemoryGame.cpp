#include <cstdlib>
#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "GLSLloader.hpp"
#include "GameController.hpp"

using namespace glm;

void createVertexArray()
{
    GLuint vertexArrayID;
    glGenVertexArrays(1, &vertexArrayID);
    glBindVertexArray(vertexArrayID);
}

bool isInRange(int num, int min, int mx)
{
    return min <= num && num <= mx;
}

void printRound(int round)
{
    std::cout << "\t\tRUNDA " << round << "\n";
}

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
    int numRows = 4, numColumns = 4, numColors = 6, numSigns = 3;
    int round = 1, cur = 0, prev = -1;
    bool check = false;

    switch(argc)
    {
        case 5:
            numSigns = atoi( argv[4] );

        case 4:
            numColors = atoi( argv[3] );

        case 3:
            numColumns = atoi( argv[2] );

        case 2:
            numRows = atoi( argv[1] );
    }

    if( !isInRange(numRows, 1, 12) )
    {
        std::cerr << "FAILURE! INCORRECT NUMBER OF ROWS\n";
        return -1;
    }

    if( !isInRange(numColumns, 1, 12) )
    {
        std::cerr << "FAILURE! INCORRECT NUMBER OF COLUMNS\n";
        return -1;
    }

    if( !isInRange(numColors, 2, 6) )
    {
        std::cerr << "FAILURE! INCORRECT NUMBER OF CARD COLORS\n";
        return -1;
    }

    if( !isInRange(numSigns, 1, 3) )
    {
        std::cerr << "FAILURE! INCORRECT NUMBER OF CARD SIGNS\n";
        return -1;
    }

    if( (numRows*numColumns)%2 != 0)
    {
        std::cerr << "FAILURE! ODD NUMBER OF CARDS\n";
        return -1;
    }

    if(!glfwInit())
    {
        std::cerr << "FAILED TO INITIALIZE GLFW\n";
        return -1;
    }

    glfwHints();

    GLFWwindow * window = glfwCreateWindow(1024, 768, "Memory Game", NULL, NULL);

    if(window == NULL)
    {
        std::cerr << "FAILED TO OPEN A NEW WINDOW\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glewExperimental = true;

    if(glewInit() != GLEW_OK)
    {
        std::cerr << "FAILED TO INITIALIZE GLEW\n";
        return -1;
    }

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    GLuint programID = loadShaders("VertexShader.glsl", "FragmentShader.glsl");

    createVertexArray();

    GameController * ctrl =
        new GameController(std::make_pair(numRows, numColumns), numColors, numSigns);
    int cardsLeft = numRows*numColumns;
    bool goToNext = false;

    printRound(round);

    do
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(programID);

        ctrl->drawGame( programID, std::make_pair(prev, cur), (check || goToNext) );

        glfwSwapBuffers(window);

        if(cardsLeft == 0)
            glfwPollEvents();
        else if(check)
        {
            if( ctrl->checkSame(prev, cur) )
            {
                ctrl->setVisible(prev);
                ctrl->setVisible(cur);
                cardsLeft -= 2;
                std::cout << "\tTRAFIONO!!!\n";
            }

            if(cardsLeft == 0)
            {
                std::cout << "WYGRANA W " << round << " RUNDACH\n";
                goToNext = true;
                continue;
            }

            round++;
            check = false;
            goToNext = true;
            printRound(round);
        }
        else
        {
            glfwWaitEvents();

            int keyCode = ctrl->checkKeyPress(window);

            if(keyCode != -1)
            {
                ctrl->checkKeyRelease(window, keyCode);

                if(goToNext)
                {
                    prev = -1;
                    goToNext = false;
                }
            }

            if(keyCode == 0 && !ctrl->isVisible(cur) )
            {
                if(prev == -1)
                    prev = cur;
                else if(prev != cur)
                    check = true;
            }
            else if(keyCode > 0)
                cur = ctrl->moveFrame(keyCode, cur);
        }
    }
    while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);

    if(cardsLeft != 0)
        std::cout << "PRZERWANO GRĘ\n\n";

    glfwTerminate();
    delete ctrl;

    return 0;
}

