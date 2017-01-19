#include <cstdlib>
#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "GLGameDrawer.hpp"

using namespace glm;

bool GLGameDrawer::isVisible(int i)
{
    return visible[i];
}

void GLGameDrawer::setVisible(int i)
{
    visible[i] = true;
}

void GLGameDrawer::drawSquares(GLuint pID, int col, std::pair <int, int> tr, int frameOffset)
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

void GLGameDrawer::drawSign(GLuint pID, int i)
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

void GLGameDrawer::drawGame(GLuint pID, GLuint vBuf, const std::pair <int, int> & pos, bool isCurVisible)
{
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vBuf);
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

int GLGameDrawer::checkKeyPress(GLFWwindow * window)
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

void GLGameDrawer::checkKeyRelease(GLFWwindow * window, int key)
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

int GLGameDrawer::moveFrame(int key, int cur)
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

bool GLGameDrawer::checkSame(int prev, int cur)
{
    return colorCodes[prev] == colorCodes[cur] && signCodes[prev] == signCodes[cur];
}

void createVertexArray()
{
    GLuint vertexArrayID;
    glGenVertexArrays(1, &vertexArrayID);
    glBindVertexArray(vertexArrayID);
}

GLuint createVertexBuffer()
{
    static const GLfloat vertexBufferData[] =
        {-0.9f, -0.9f, 0.9f, -0.9f, 0.9f, 0.9f, -0.9f, 0.9f,    // square
        -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f,     // frame
        0.0f, 0.7f, 0.0f, -0.7f,                                // pipe
        -0.7f, -0.7f, 0.7f, 0.7f, 0.7f, -0.7f, -0.7f, 0.7f,     // cross
        0.0f, 0.7f, -0.7f, -0.7f, 0.7f, -0.7f};                 // triangle
    
    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBufferData), vertexBufferData, GL_STATIC_DRAW);
    
    return vertexBuffer;
}

