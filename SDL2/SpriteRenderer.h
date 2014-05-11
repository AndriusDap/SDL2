#pragma once
#include "Includes.h"
#include "BasicEffect.h"
#include "Glyphs.h"
const int COLLUMN_COUNT = 2;
const int ROW_COUNT = 2;

class SpriteRenderer
{
	GLuint texture;
	vector<float> CoordinateBuffer;
	vector<float> TextureBuffer;
	void InsertTextureCoordinates(int texturePosition);
	void InsertCoordinates(float x, float y, float size);

	
	void InsertTextureCoordinates(float x, float y, float w, float h);
	void InsertCoordinates(float left, float right, float bottom, float top);

	Glyph letters[200];
	BasicEffect Shader;	
	GLuint buffers[2];
public:
	SpriteRenderer();
	void Flip(glm::mat4 Projection, glm::mat4 View);
	void Render(glm::vec2 position, float size, int texturePosition);
	void Render(float x, float y, float size, int texturePosition);
	void RenderText(float x, float y, string text);
	~SpriteRenderer();
};

