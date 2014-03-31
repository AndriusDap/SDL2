#pragma once

#include "Includes.h"
#include "IRenderable.h"
#include "BasicEffect.h"

#ifndef GLContext
#define GLContext SDL_GLContext
#endif


class Graphics
{
private:
	glm::mat4 ProjectionMatrix;
	glm::mat4 ViewMatrix;
	BasicEffect Shader;

	GLuint SquareVBO;
	GLuint SquareUV;
	GLuint LastTexture;

public:	
	GLFWwindow* main_window;
	Graphics(int w, int h);
	void Flip();
	glm::mat4 Projection();
	void Render(IRenderable &s);
	void StartRendering();
	~Graphics(void);

private:
	void InitializeRectangle();

};

