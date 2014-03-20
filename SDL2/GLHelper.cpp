#pragma once
#include "GLHelper.h"
#include <cassert>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <SDL_image.h>


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
		OutputDebugStringA(&shaderInfoLog[0]);
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
		OutputDebugStringA(&programInfoLog[0]);
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

SDL_Surface* PrepareSurface(SDL_Surface* source)
{
	// Change format to one that can be used with opengl
	SDL_PixelFormat format = {0};	
	format.format = SDL_PIXELFORMAT_RGBA8888;
	format.palette = nullptr;
	format.BitsPerPixel = 32;
	format.BytesPerPixel = 4;
	format.Rmask = 0xff000000;
	format.Gmask = 0x00ff0000;
	format.Bmask = 0x0000ff00;
	format.Amask = 0x000000ff;

	auto formatted = SDL_ConvertSurface(source, &format, 0);
	Uint32* pixels = (Uint32*) formatted->pixels;
	// Flip horizontaly
	int w = formatted->w;
	for(int y = 0; y < formatted->h; y++)
	{
		for(int x0 = 0, x1 = formatted->w - 1; x0 < x1; x0++, x1--)
		{
			swap((pixels + y * w)[x0], (pixels + y * w)[x1]);
		}
	}
	return formatted;
}

unordered_map<string, GLuint> textures;
GLuint GLHelper::LoadTexture(string filePath)
{
	try
	{
		return textures.at(filePath);
	} 
	catch (out_of_range&)
	{
		auto bmp = IMG_Load(filePath.c_str());
		auto preparedTexture = PrepareSurface(bmp);
	
		GLuint texture;
		gl::GenTextures(1, &texture);		
		gl::BindTexture(gl::TEXTURE_2D, texture);	
		gl::TexStorage2D(gl::TEXTURE_2D, 1, gl::RGBA8, preparedTexture->w, preparedTexture->h);
		gl::TexSubImage2D(gl::TEXTURE_2D, 0, 0, 0, preparedTexture->w, preparedTexture->h, gl::RGBA, gl::UNSIGNED_INT_8_8_8_8, preparedTexture->pixels);	
		CheckGlErrors();

		SDL_FreeSurface(bmp);
		SDL_FreeSurface(preparedTexture);
		textures[filePath] = texture;
		return texture;
	}
}