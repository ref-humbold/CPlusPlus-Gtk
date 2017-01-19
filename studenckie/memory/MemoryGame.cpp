#include <cstdlib>
#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "GLSLloader.hpp"
#include "GLGameDrawer.hpp"

using namespace glm;

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

    // ograniczenia na wartości wprowadzane przez użytkownika

    if( !isInRange(numRows, 1, 12) )
    {
        fprintf(stderr, "FAILURE! INCORRECT NUMBER OF ROWS\n");
        return -1;
    }

    if( !isInRange(numColumns, 1, 12) )
    {
        fprintf(stderr, "FAILURE! INCORRECT NUMBER OF COLUMNS\n");
        return -1;
    }

    if( !isInRange(numColors, 2, 6) )
    {
        fprintf(stderr, "FAILURE! INCORRECT NUMBER OF CARD COLORS\n");
        return -1;
    }

    if( !isInRange(numSigns, 1, 3) )
    {
        fprintf(stderr, "FAILURE! INCORRECT NUMBER OF CARD SIGNS\n");
        return -1;
    }

    if( (numRows*numColumns)%2 != 0)
    {
        fprintf(stderr, "FAILURE! ODD NUMBER OF CARDS\n");
        return -1;
    }

    // inicjalizacja OpenGL

    if(!glfwInit())
    {
        fprintf(stderr, "FAILED TO INITIALIZE GLFW\n");
        return -1;
    }

    glfwHints();

    GLFWwindow * window = glfwCreateWindow(1024, 768, "Memory Game", NULL, NULL);

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
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    GLuint programID = loadShaders("VertexShader.glsl", "FragmentShader.glsl");

    createVertexArray();
    GLuint vertexBuffer = createVertexBuffer();

    // inicjalizacja planszy

    GLGameDrawer * gameDrawer = new GLGameDrawer(std::make_pair(numRows, numColumns), numColors, numSigns);
    int cardsLeft = numRows*numColumns, waitTillEnd = 1;
    bool goToNext = false;

    // kontrola gry

    printRound(round);

    do
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(programID);

        gameDrawer->drawGame( programID, vertexBuffer, std::make_pair(prev, cur), (check || goToNext) );

        glfwSwapBuffers(window);

        if(cardsLeft == 0)
            --waitTillEnd;
        else if(check)
        {
            // sprawdzamy odsłonięte karty

            if( gameDrawer->checkSame(prev, cur) )
            {
                gameDrawer->setVisible(prev);
                gameDrawer->setVisible(cur);
                cardsLeft -= 2;
                std::cout << "\tTRAFIONO!!!\n";
            }

            if(cardsLeft == 0)
            {
                std::cout << "WYGRANA W " << round << " RUNDACH\n";
                waitTillEnd = 1000000;
            }

            round++;
            check = false;
            goToNext = true;
            printRound(round);
        }
        else
        {
            // sprawdzamy wciśnięcie klawiszy nawigacji lub spacji

            glfwWaitEvents();

            int keyCode = gameDrawer->checkKeyPress(window);

            if(keyCode != -1)
            {
                gameDrawer->checkKeyRelease(window, keyCode);

                if(goToNext)
                {
                    prev = -1;
                    goToNext = false;
                }
            }

            if(keyCode == 0 && !gameDrawer->isVisible(cur) )
            {
                if(prev == -1)
                    prev = cur;
                else if(prev != cur)
                    check = true;
            }
            else if(keyCode > 0)
                cur = gameDrawer->moveFrame(keyCode, cur);
        }
    }
    while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0
        && waitTillEnd > 0);

    if(cardsLeft != 0)
        std::cout << "PRZERWANO GRĘ\n\n";

    glfwTerminate();
    delete gameDrawer;

    return 0;
}

