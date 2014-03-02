#pragma once

#include <glload\gl_4_3.hpp>
#include <glload\gl_load.hpp>
#include "Includes.h"
#include "IRenderable.h"
#include "BasicEffect.h"

#ifndef GLContext
#define GLContext SDL_GLContext
#endif


class Graphics
{
private:
	SDL_Window *main_window;
	SDL_GLContext main_context;
	glm::mat4 ProjectionMatrix;
	glm::mat4 ViewMatrix;
	BasicEffect Shader;

	GLuint SquareVBO;
	GLuint SquareUV;
	GLuint LastTexture;

public:
	Graphics(int w, int h);
	void Flip();
	glm::mat4 Projection();
	void Render(IRenderable &s);
	void StartRendering();
	//void Render(Sprite *s, size_t count);
	~Graphics(void);

private:
	void InitializeRectangle();

};

