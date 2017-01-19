#ifndef GLGAMEDRAWER_HPP
#define GLGAMEDRAWER_HPP

#include <cstdlib>
#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

using namespace glm;

class GLGameDrawer
{
    private:
    std::pair <int, int> size;
    std::vector <int> colorCodes;
    std::vector <int> signCodes;
    std::vector < std::pair <int, int> > transforms;
    std::vector <bool> visible;
    
    public:
    GLGameDrawer(const std::pair <int, int> & size, int numColors, int numSigns) : size{size}
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
    }
    
    bool isVisible(int i);
    void setVisible(int i);
    
    void drawSquares(GLuint pID, int col, std::pair <int, int> tr, int frameOffset);
    void drawSign(GLuint pID, int i);
    void drawGame(GLuint pID, GLuint vBuf, const std::pair <int, int> & pos, bool isCurVisible);
    
    int checkKeyPress(GLFWwindow * window);
    void checkKeyRelease(GLFWwindow * window, int key);
    
    int moveFrame(int key, int cur);
    
    bool checkSame(int prev, int cur);
};

void createVertexArray();

GLuint createVertexBuffer();

#endif

