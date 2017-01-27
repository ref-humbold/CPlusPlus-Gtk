#include "GameController.hpp"

using namespace glm;

GameController::GameController(const std::pair <int, int> & size, int numColors, int numSigns) :
    vbData{-0.9f, -0.9f, 0.9f, -0.9f, 0.9f, 0.9f, -0.9f, 0.9f,  // square
           -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f,  // frame
           0.0f, 0.7f, 0.0f, -0.7f,                             // pipe
           -0.7f, -0.7f, 0.7f, 0.7f, 0.7f, -0.7f, -0.7f, 0.7f,  // cross
           0.0f, 0.7f, -0.7f, -0.7f, 0.7f, -0.7f},              // triangle
    size{size}
{
    srand( time(NULL) );

    std::vector <bool> isSet(size.first*size.second, false);
    int elemSet = 0;

    visible.resize(size.first*size.second, false);
    colorCodes.resize(size.first*size.second);
    signCodes.resize(size.first*size.second);

    for(float i = -size.first+1; i <= size.first; i += 2)
        for(float j = -size.second+1; j <= size.second; j += 2)
            transforms.push_back( std::make_pair(i, j) );

    while(elemSet != (int)isSet.size())
    {
        int i, j, col = rand()%numColors+1, sgn = rand()%numSigns;

        do
            i = rand()%isSet.size();
        while( isSet[i] );

        do
            j = rand()%isSet.size();
        while(isSet[j] || j == i);

        colorCodes[i] = col;
        signCodes[i] = sgn;
        colorCodes[j]= col;
        signCodes[j] = sgn;
        isSet[i] = true;
        isSet[j] = true;
        elemSet += 2;
    }

    static const GLfloat vertexBufferData[] =
    {-0.9f, -0.9f, 0.9f, -0.9f, 0.9f, 0.9f, -0.9f, 0.9f,    // square
    -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f,     // frame
    0.0f, 0.7f, 0.0f, -0.7f,                                // pipe
    -0.7f, -0.7f, 0.7f, 0.7f, 0.7f, -0.7f, -0.7f, 0.7f,     // cross
    0.0f, 0.7f, -0.7f, -0.7f, 0.7f, -0.7f};                 // triangle

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBufferData), vbData, GL_STATIC_DRAW);
}

bool GameController::isVisible(int i)
{
    return visible[i];
}

void GameController::setVisible(int i)
{
    visible[i] = true;
}

void GameController::drawGame(GLuint pID, const std::pair <int, int> & pos, bool isCurVisible)
{
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void *)0);

    drawSquares(pID, 10, transforms[pos.second], 4);

    for(int i = 0; i < size.first*size.second; i++)
        if( visible[i] || i == pos.first || (isCurVisible && i == pos.second) )
        {
            drawSquares(pID, colorCodes[i], transforms[i], 0);
            drawSign(pID, i);
        }
        else
            drawSquares(pID, 0, transforms[i], 0);

    glDisableVertexAttribArray(0);
}

int GameController::checkKeyPress(GLFWwindow * window)
{
    int action = GLFW_PRESS;

    if(glfwGetKey(window, GLFW_KEY_SPACE) == action)
        return 0;
    else if(glfwGetKey(window, GLFW_KEY_UP) == action)
        return 1;
    else if(glfwGetKey(window, GLFW_KEY_DOWN) == action)
        return 2;
    else if(glfwGetKey(window, GLFW_KEY_LEFT) == action)
        return 3;
    else if(glfwGetKey(window, GLFW_KEY_RIGHT) == action)
        return 4;

    return -1;
}

void GameController::checkKeyRelease(GLFWwindow * window, int key)
{
    int action = GLFW_RELEASE;

    switch(key)
    {
        case 0:
            while(glfwGetKey(window, GLFW_KEY_SPACE) != action)
                glfwWaitEvents();

            break;

        case 1:
            while(glfwGetKey(window, GLFW_KEY_UP) != action)
                glfwWaitEvents();

            break;

        case 2:
            while(glfwGetKey(window, GLFW_KEY_DOWN) != action)
                glfwWaitEvents();

            break;

        case 3:
            while(glfwGetKey(window, GLFW_KEY_LEFT) != action)
                glfwWaitEvents();

            break;

        case 4:
            while(glfwGetKey(window, GLFW_KEY_RIGHT) != action)
                glfwWaitEvents();

            break;
    }

    return;
}

int GameController::moveFrame(int key, int cur)
{
    int rw = cur/size.second, cl = cur%size.second;

    switch(key)
    {
        case 1:
            cur = (rw+1)%size.first*size.second+cl;
            break;

        case 2:
            cur = (rw-1+size.first)%size.first*size.second+cl;
            break;

        case 3:
            cur = rw*size.second+(cl-1+size.second)%size.second;
            break;

        case 4:
            cur = rw*size.second+(cl+1)%size.second;
            break;
    }

    return cur;
}

bool GameController::checkSame(int prev, int cur)
{
    return colorCodes[prev] == colorCodes[cur] && signCodes[prev] == signCodes[cur];
}

void GameController::drawSquares(GLuint pID, int col, std::pair <int, int> tr, int frameOffset)
{
    GLint scale = glGetUniformLocation(pID, "scale");
    GLint transform = glGetUniformLocation(pID, "transform");
    GLint color = glGetUniformLocation(pID, "fragmentColor");

    glUniform2f(scale, 0.8f/size.second, 0.8f/size.first);
    glUniform2f(transform, tr.second, tr.first);

    switch(col)
    {
        case 4:
            glUniform3f(color, 1.0f, 0.0f, 0.0f); //red
            break;

        case 2:
            glUniform3f(color, 0.0f, 1.0f, 0.0f); //green
            break;

        case 1:
            glUniform3f(color, 0.0f, 0.0f, 1.0f); //blue
            break;

        case 3:
            glUniform3f(color, 0.0f, 1.0f, 1.0f); //cyan
            break;

        case 5:
            glUniform3f(color, 1.0f, 0.0f, 1.0f); //magenta
            break;

        case 6:
            glUniform3f(color, 1.0f, 1.0f, 0.0f); //yellow
            break;

        case 0:
            glUniform3f(color, 0.0f, 0.0f, 0.0f); //black
            break;

        case 10:
            glUniform3f(color, 0.5f, 0.5f, 0.5f); //grey
            break;
    }

    glDrawArrays(GL_TRIANGLE_FAN, frameOffset, 4);
}

void GameController::drawSign(GLuint pID, int i)
{
    GLint scale = glGetUniformLocation(pID, "scale");
    GLint transform = glGetUniformLocation(pID, "transform");
    GLint color = glGetUniformLocation(pID, "fragmentColor");

    glUniform2f(scale, 0.8f/size.second, 0.8f/size.first);
    glUniform2f(transform, transforms[i].second, transforms[i].first);
    glUniform3f(color, 0.0f, 0.0f, 0.0f);

    switch( signCodes[i] )
    {
        case 0:
            glDrawArrays(GL_LINES, 8, 2);
            break;

        case 1:
            glDrawArrays(GL_LINES, 10, 2);
            glDrawArrays(GL_LINES, 12, 2);
            break;

        case 2:
            glDrawArrays(GL_LINE_LOOP, 14, 3);
            break;
    }
}
