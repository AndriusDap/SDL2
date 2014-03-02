#pragma once
#include <glload\gl_4_2.hpp>
#include <string>
#include "Includes.h"
using namespace std;

namespace GLHelper 
{
	GLuint LoadShader(string filePath, GLuint shaderType);
	GLuint CreateProgram(GLuint fragmentShader, GLuint vertexShader);
	GLuint LoadTexture(string filePath);
}