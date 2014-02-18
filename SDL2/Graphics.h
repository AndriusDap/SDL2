#pragma once

#include <glload\gl_4_3.hpp>
#include <glload\gl_load.hpp>
#include "Includes.h"

#ifndef GLContext
#define GLContext SDL_GLContext
#endif


class Graphics
{
private:
	SDL_Window *main_window;
	SDL_GLContext main_context;
	glm::mat4 ProjectionMatrix;

public:
	Graphics(int w, int h);
	void Flip();
	glm::mat4 Projection();
	~Graphics(void);
};

