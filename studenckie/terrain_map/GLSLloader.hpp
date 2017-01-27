#ifndef GLSLLOADER_HPP
#define GLSLLOADER_HPP

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

using namespace glm;

void compileShader(GLuint ShaderID, std::string ShaderCode, char const * file_path);

GLuint linkProgram(GLuint VertexShaderID, GLuint FragmentShaderID);

GLuint prepareShader(const char * file_path, GLenum shader_type);

GLuint loadShaders(const char * vertex_file_path, const char * fragment_file_path);

#endif
