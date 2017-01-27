#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "GLSLloader.hpp"

using namespace glm;

void compileShader(GLuint ShaderID, std::string ShaderCode, char const * file_path)
{
    GLint Result = GL_FALSE;
    int InfoLogLength;

    // Compile shader
    char const * SourcePointer = ShaderCode.c_str();

    printf("Compiling shader : %s\n", file_path);
    glShaderSource(ShaderID, 1, &SourcePointer, NULL);
    glCompileShader(ShaderID);

    // Check shader
    glGetShaderiv(ShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(ShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);

    if (InfoLogLength > 0)
    {
        std::vector <char> ShaderErrorMessage(InfoLogLength+1);

        glGetShaderInfoLog( ShaderID, InfoLogLength, NULL, &ShaderErrorMessage[0] );
        printf( "%s\n", &ShaderErrorMessage[0] );
    }
}

GLuint linkProgram(GLuint VertexShaderID, GLuint FragmentShaderID)
{
    GLint Result = GL_FALSE;
    int InfoLogLength;

    // Link the program
    GLuint ProgramID = glCreateProgram();

    printf("Linking program\n");
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);

    // Check the program
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);

    if(InfoLogLength > 0)
    {
        std::vector <char> ProgramErrorMessage(InfoLogLength+1);

        glGetProgramInfoLog( ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0] );
        printf( "%s\n", &ProgramErrorMessage[0] );
    }

    return ProgramID;
}

GLuint prepareShader(const char * file_path, GLenum shader_type)
{
    // Read the shader code from the file
    std::string shaderCode;
    std::ifstream shaderStream(file_path, std::ios::in);

    if(shaderStream.is_open())
    {
        std::string Line = "";

        while( getline(shaderStream, Line) )
            shaderCode += "\n" + Line;

        shaderStream.close();
    }
    else
    {
        printf("Impossible to open %s.\n", file_path);
        return -1;
    }

    GLuint shaderID = glCreateShader(shader_type);
    compileShader(shaderID, shaderCode, file_path);

    return shaderID;
}

GLuint loadShaders(const char * vertex_file_path, const char * fragment_file_path)
{
    // Create and compile shaders
    GLuint VertexShaderID = prepareShader(vertex_file_path, GL_VERTEX_SHADER);
    GLuint FragmentShaderID = prepareShader(fragment_file_path, GL_FRAGMENT_SHADER);

    GLuint ProgramID = linkProgram(VertexShaderID, FragmentShaderID);

    glDetachShader(ProgramID, VertexShaderID);
    glDetachShader(ProgramID, FragmentShaderID);

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

    return ProgramID;
}
