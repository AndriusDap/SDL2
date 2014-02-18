#pragma once
#include <glload\gl_4_2.hpp>
#include <string>
#include <vector>
#include "Includes.h"

using namespace std;
namespace GLHelper 
{
	GLuint LoadShader(string filePath, GLuint shaderType);
	GLuint CreateProgram(GLuint fragmentShader, GLuint vertexShader);
	void LoadModel(string filePath, vector<float> vertices, vector<int> drawSequence);
}