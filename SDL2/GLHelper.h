#pragma once
#include "Includes.h"
using namespace std;

namespace GLHelper 
{
	GLuint LoadShader(string filePath, GLuint shaderType);
	GLuint CreateProgram(GLuint fragmentShader, GLuint vertexShader);
	GLuint LoadTexture(string filePath);
	string GetHighscore();
	int GetLastScore();
	void SetHighscore(int score);
	void SetHighscore(int score, string name);

}