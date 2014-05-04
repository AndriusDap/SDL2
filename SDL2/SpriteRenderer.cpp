#include "Includes.h"
#include "SpriteRenderer.h"
#include "GLHelper.h"


SpriteRenderer::SpriteRenderer()
{
	Shader.init();
	texture = GLHelper::LoadTexture("Assets/SpriteSheet.png");
	glGenBuffers(2, buffers);
}


void SpriteRenderer::Render(glm::vec2 position, float size, int texturePosition)
{
	Render(position.x, position.y, size, texturePosition);
}

void SpriteRenderer::Render(float x, float y, float size, int texturePosition)
{
	this->InsertTextureCoordinates(texturePosition);
	this->InsertCoordinates(x, y, size);
}

void SpriteRenderer::Flip(glm::mat4 Projection, glm::mat4 View)
{
	if(CoordinateBuffer.size() > 0) 
	{
	
		//Fill buffers
		
		glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * CoordinateBuffer.size(), &CoordinateBuffer[0], GL_STREAM_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);

		glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * TextureBuffer.size(), &TextureBuffer[0], GL_STREAM_DRAW);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*) 0);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture);

		Shader.begin();
		Shader.setModel(glm::mat4());
		Shader.setProjection(Projection);	
		Shader.setView(View);
		Shader.setTexture(1);

		glDrawArrays(GL_TRIANGLES, 0, TextureBuffer.size());

		TextureBuffer.clear();
		CoordinateBuffer.clear();
	}
}

SpriteRenderer::~SpriteRenderer()
{
	glDeleteBuffers(2, buffers);
}

void SpriteRenderer::InsertTextureCoordinates(int texturePosition)
{
	assert(texturePosition < ROW_COUNT * COLLUMN_COUNT);
	int collumn = texturePosition % ROW_COUNT;
	int row = texturePosition / COLLUMN_COUNT;
	float height = 1.0f / ROW_COUNT;
	float width = 1.0f / COLLUMN_COUNT;

	float x = collumn * width;
	float y = row * height;

	/*
	float UV[] = {
		x + width, y + height,
		x + 0.0f,  y + 0.0f,
		x + width, y + 0.0f,
		x + width, y + height,
		x + 0.0f,  y + height,
		x + 0.0f,  y + 0.0f,
	};
	*/
	
	TextureBuffer.emplace_back(x + width);
	TextureBuffer.emplace_back(y + height);
	TextureBuffer.emplace_back(x);
	TextureBuffer.emplace_back(y);
	TextureBuffer.emplace_back(x + width);
	TextureBuffer.emplace_back(y);
	TextureBuffer.emplace_back(x + width);
	TextureBuffer.emplace_back(y + height);
	TextureBuffer.emplace_back(x);
	TextureBuffer.emplace_back(y + height);
	TextureBuffer.emplace_back(x);
	TextureBuffer.emplace_back(y);

}

void SpriteRenderer::InsertCoordinates(float x, float y, float size)
{
	/*
	float SquareCoordinateArray[] = {
		0.5f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
	};
	*/
	float left = x - size / 2;
	float right = x + size / 2;
	float top = y - size / 2;
	float bottom = y + size / 2; 

	CoordinateBuffer.emplace_back(right);
	CoordinateBuffer.emplace_back(bottom);
	CoordinateBuffer.emplace_back(0.0f);
	CoordinateBuffer.emplace_back(left);
	CoordinateBuffer.emplace_back(top);
	CoordinateBuffer.emplace_back(0.0f);
	CoordinateBuffer.emplace_back(right);
	CoordinateBuffer.emplace_back(top);
	CoordinateBuffer.emplace_back(0.0f);
	CoordinateBuffer.emplace_back(right);
	CoordinateBuffer.emplace_back(bottom);
	CoordinateBuffer.emplace_back(0.0f);
	CoordinateBuffer.emplace_back(left);
	CoordinateBuffer.emplace_back(bottom);
	CoordinateBuffer.emplace_back(0.0f);
	CoordinateBuffer.emplace_back(left);
	CoordinateBuffer.emplace_back(top);
	CoordinateBuffer.emplace_back(0.0f);
}