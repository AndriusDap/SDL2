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
	vector<IRenderable> FrameQueue;
	size_t FrameCursor;
	static const size_t FrameQueueLength = 1000;
	GLuint ModelTransformationBuffer;

	glm::mat4 ProjectionMatrix;
	glm::mat4 ViewMatrix;
	BasicEffect Shader;

	GLuint SquareVBO;
	GLuint SquareUV;
	GLuint LastTexture;
	
	void FlushBuffer();
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

