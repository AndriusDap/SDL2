#pragma once
#include "Includes.h"
#include "GLHelper.h"
class TextFactory
{
private:
	struct DrawCall {
		string text;
		float x;
		float y;
	};

	unordered_map<char, pair<float, float>> TextureCoordinates;
	unordered_map<string, GLuint> Strings;
	GLuint Texture;
	GLuint Program;
	
	GLuint XOffsetHandle;
	GLuint YOffsetHandle;
	GLuint ColorHandle;
	GLuint TextureHandle;
	GLuint CameraHandle;
	float Height;

	//Buffers that should be deleted on cache flush.
	vector<GLuint> buffers;

	vector<DrawCall> drawCalls;
public:	
	TextFactory();
	virtual ~TextFactory();

	//Gets string dimensions without creating it.
	pair<float, float> Measure(string text);

	//Prepare string for rendering - creates buffers on gpu side.
	void Prepare(string text);

	//Draw text at given location with optional scale.
	void RenderText(string text, float x, float y);

	//Push text to screen
	void Render(glm::mat4 Camera);
	//Removes all cached strings, cleans buffers.
	void FlushCache();
};


