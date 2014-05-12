#pragma once
#include "Includes.h"
using namespace std;

namespace GLHelper 
{
	GLuint LoadShader(string filePath, GLuint shaderType);
	GLuint CreateProgram(GLuint fragmentShader, GLuint vertexShader);
	GLuint LoadTexture(string filePath);
	int GetHighscore();
	int GetLastScore();
	void SetHighscore(int score);

}