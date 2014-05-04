#pragma once

#include "Includes.h"
#include "IRenderable.h"
#include "BasicEffect.h"
#include "SpriteRenderer.h"

class Graphics
{
private:
	glm::mat4 ProjectionMatrix;
	glm::mat4 ViewMatrix;
	BasicEffect Shader;

	GLuint SquareVBO;
	GLuint SquareUV;
	GLuint LastTexture;
	GLuint TexturePack;

	SpriteRenderer* spriteRenderer;
public:	
	GLFWwindow* main_window;
	Graphics(int w, int h);
	void Flip();
	glm::mat4 Projection();
	void Render(IRenderable &s);
	void StartRendering();
	~Graphics(void);
	void RenderPointSprite(float x, float y, float size, int spriteId);

private:
	void InitializeRectangle();

};

