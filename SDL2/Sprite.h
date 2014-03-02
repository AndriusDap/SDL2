#pragma once
#include "Includes.h"
#include "IRenderable.h"
class Sprite : public IRenderable
{
private:
	float X, Y;
	float Scale;
	float Rotation;
	
	glm::mat4 Model;
	bool Dirty;
	void getModel();
public:
	Sprite(void);
	virtual ~Sprite(void);
	glm::mat4 getTransformation();
	GLuint Texture;
	GLuint getTexture();
	void setScale(float scale);
	void setTranslation(float x, float y);
	void setRotation(float angle);
};

