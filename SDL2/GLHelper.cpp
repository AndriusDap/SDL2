#include "GLHelper.h"
#include <cassert>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>


GLuint GLHelper::LoadShader(std::string filePath, GLuint shaderType)
{
	//Create shader id
	GLuint shaderId = gl::CreateShader(shaderType);
	assert(shaderId);

	//Read source code from file
	std::stringstream shaderCode;
	std::ifstream source(filePath, std::ios::in);
	assert(source.is_open());
	std::string line;
	while(getline(source, line))
	{
		shaderCode << line << "\n";
	}
	source.close();


	//Compile shader
	std::string s = shaderCode.str();
	s += "\0";
	const char * sourcePointer = s.c_str();
	const GLint length = s.length();
	gl::ShaderSource(shaderId, 1, &sourcePointer, &length);
	gl::CompileShader(shaderId);

	//Check for errors
	GLint result = gl::FALSE_;
	int infoLogLength = 0;
	gl::GetShaderiv(shaderId, gl::COMPILE_STATUS, &result);
	gl::GetShaderiv(shaderId, gl::INFO_LOG_LENGTH, &infoLogLength);
	std::vector<char> shaderInfoLog(infoLogLength);

	std::cout << "Shader " << shaderType << " compilation status: " << result << "\n";
	if(infoLogLength > 0)
	{	
		gl::GetShaderInfoLog(shaderId, infoLogLength, NULL, &shaderInfoLog[0]);
		std::cout << "Info log: " << &shaderInfoLog[0] << std::endl;
		OutputDebugString(&shaderInfoLog[0]);
	}
	return shaderId;
}

void PrintProgramLog(GLuint programId)
{

	GLint result = gl::FALSE_;
	int infoLogLength = 0;
	gl::GetProgramiv(programId, gl::LINK_STATUS, &result);
	gl::GetProgramiv(programId, gl::INFO_LOG_LENGTH, &infoLogLength);


	std::cout << "Program " << programId << " linking status: " << result << "\n";
	if(infoLogLength > 0)
	{	
		std::vector<char> programInfoLog(infoLogLength);
		gl::GetProgramInfoLog(programId, infoLogLength, NULL, &programInfoLog[0]);
		std::cout << "Info log: " << &programInfoLog[0] << std::endl;
		OutputDebugString(&programInfoLog[0]);
	}
}



GLuint GLHelper::CreateProgram(GLuint fragmentShader, GLuint vertexShader)
{
	assert(fragmentShader);
	assert(vertexShader);
	GLuint programId = gl::CreateProgram();
	assert(programId);

	gl::AttachShader(programId, vertexShader);
	gl::AttachShader(programId, fragmentShader);
	
	gl::LinkProgram(programId);

	PrintProgramLog(programId);
	return programId;
}

void GLHelper::LoadModel(string filePath, vector<float> vertices, vector<int> drawSequence)
{

}