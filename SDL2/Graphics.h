#pragma once

#include "Includes.h"
#include "IRenderable.h"
#include "BasicEffect.h"
#include "TextFactory.h"

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

	TextFactory *Text;

public:
	Graphics(int w, int h);
	void Flip();
	glm::mat4 Projection();
	void Render(IRenderable &s);
	void StartRendering();
	void Drawtext(string text, float x, float y);
	//void Render(Sprite *s, size_t count);
	~Graphics(void);

private:
	void InitializeRectangle();

};

