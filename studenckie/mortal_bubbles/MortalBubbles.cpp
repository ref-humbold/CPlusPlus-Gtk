#include <cstdlib>
#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "GLSLloader.hpp"
#include "GameControler.hpp"

using namespace glm;

bool vecDifferent(vec3 v1, vec3 v2)
{
    return v1[0] != v2[0] || v1[1] != v2[1] || v1[2] != v2[2];
}

void createVertexArray()
{
    GLuint vertexArrayID;
    glGenVertexArrays(1, &vertexArrayID);
    glBindVertexArray(vertexArrayID);
}

void glfwHints()
{
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

int main()
{
    if(!glfwInit())
    {
        std::cerr << "FAILED TO INITIALIZE GLFW\n";
        return -1;
    }

    glfwHints();

    GLFWwindow * window = glfwCreateWindow(1024, 768, "Mortal Bubbles", NULL, NULL);

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
    glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, GL_TRUE);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    GLuint programID = loadShaders("VertexShader.glsl", "FragmentShader.glsl");

    createVertexArray();

    glDisable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    srand( time(0) );

    std::vector <int> keys = {GLFW_KEY_TAB, GLFW_KEY_W, GLFW_KEY_X, GLFW_KEY_E, GLFW_KEY_Z,
        GLFW_KEY_A, GLFW_KEY_D, GLFW_KEY_UP, GLFW_KEY_DOWN};
    vec3 mouseBegin, mouseEnd;

    GameControler * ctrl = new GameControler(window);

    int gameLevel = -1;
    bool isRestarted = true, mouseClicked = false;
    GLfloat timer = 0.0f, counter = 0.0f;

    std::cout << "\n\tRUNDA 1: PUNKTY = " << ctrl->points << "\n";
    ctrl->restart();

    do
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(programID);

        ctrl->drawGame(programID);

        glfwSwapBuffers(window);
        glfwPollEvents();

        if(gameLevel > 0)
        {
            std::vector <bool> movesMask(6, false);
            std::vector <bool> pressed = ctrl->checkKeyPress(window, keys);

            for(unsigned int i = 0; i < pressed.size(); ++i)
                if( pressed[i] )
                    switch( keys[i] )
                    {
                        case GLFW_KEY_TAB:
                            ctrl->checkTabReleased(window);
                            ctrl->changeCamera();
                            break;

                        case GLFW_KEY_W:
                            movesMask[0] = true;
                            break;

                        case GLFW_KEY_X:
                            movesMask[1] = true;
                            break;

                        case GLFW_KEY_E:
                            movesMask[2] = true;
                            break;

                        case GLFW_KEY_Z:
                            movesMask[3] = true;
                            break;

                        case GLFW_KEY_A:
                            movesMask[4] = true;
                            break;

                        case GLFW_KEY_D:
                            movesMask[5] = true;
                            break;

                        case GLFW_KEY_UP:
                            ctrl->viewScale(0.99f);
                            break;

                        case GLFW_KEY_DOWN:
                            ctrl->viewScale(1.01f);
                            break;
                    }

            if( !mouseClicked && ctrl->checkMouseAction(window, GLFW_PRESS) )
            {
                mouseBegin = ctrl->getMousePos(window);
                mouseClicked = true;
            }

            if( mouseClicked && ctrl->checkMouseAction(window, GLFW_PRESS) )
            {
                mouseEnd = ctrl->getMousePos(window);

                if( vecDifferent(mouseBegin, mouseEnd) )
                {
                    vec3 normBegin = normalize(mouseBegin);
                    vec3 normEnd = normalize(mouseEnd);
                    GLfloat cosine = dot(normBegin, normEnd);
                    GLfloat angleRad = acos( min(cosine, 1.0f) );
                    vec3 axis = normalize( cross(normBegin, normEnd) );

                    ctrl->viewRotate(angleRad, axis);
                    mouseBegin = mouseEnd;
                }
            }

            if( ctrl->checkMouseAction(window, GLFW_RELEASE) )
               mouseClicked = false;

            int bubleNumber = ctrl->checkCollisionBubble();

            if(bubleNumber > 0)
            {
                std::cout << "\tTRAFIŁEŚ W PUNKTOWANY BĄBELEK!! ZDOBYWASZ 10% WIĘCEJ PUNKTÓW\n\n";
                ctrl->points *= 1.1;
                ctrl->deletePointedBubble(bubleNumber);
            }
            else if(bubleNumber < 0)
            {
                std::cout << "\tUDERZYŁEŚ W BĄBELEK!! PRZEGRANA.\n\n";
                gameLevel = 0;
                counter = 0.0f;
                timer = glfwGetTime();
            }
            else if(ctrl->checkEndRound())
            {
                gameLevel = -gameLevel-1;
                counter = 0.0f;
                ctrl->points += 10.0;
                std::cout << "\tZA WYGRANIE RUNDY DOSTAJESZ 10 PUNKTÓW.\n";
                std::cout << "\tRUNDA " << -gameLevel << ": PUNKTY = " << ctrl->points << "\n";
                timer = glfwGetTime();
            }
            else
            {
                GLfloat delta = glfwGetTime()-timer;
                timer = glfwGetTime();
                counter += delta;
                counter = ctrl->moveBubbles(delta, counter, gameLevel);
                ctrl->movePlayer(delta, movesMask);
            }
        }
        else if(gameLevel == 0)
        {
            if(counter < 2.0f)
            {
                GLfloat delta = glfwGetTime()-timer;
                counter += delta;
                timer = glfwGetTime();
            }
            else
                break;
        }
        else if(counter >= 3.0f)
        {
            std::cout << "\t\tGRAMY!!\n\n";
            gameLevel = -gameLevel;
            isRestarted = false;
            counter = 0.0f;
        }
        else
        {
            if(counter > 1.5f && !isRestarted)
            {
                isRestarted = true;
                ctrl->restart();
            }

            counter += glfwGetTime()-timer;
            timer = glfwGetTime();
        }
    }
    while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);

    std::cout << "\tKONIEC GRY: PUNKTY = " << ctrl->points << "\n\n";
    glfwTerminate();
    delete ctrl;

    return 0;
}
