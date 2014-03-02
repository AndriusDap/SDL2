#include "Sprite.h"


Sprite::Sprite(void)
{
	X = 0;
	Y = 0;
	Scale = 1;
	Rotation = 0;

	Model = glm::mat4(1);
	Dirty = false;
}

glm::mat4 Sprite::getTransformation()
{
	if(Dirty)
	{
		Model = glm::mat4x4(1);
		Model = glm::translate(Model, glm::vec3(X, Y, 0));		
		Model = glm::rotate(Model, Rotation, glm::vec3(0, 0, 1));
		Model = glm::scale(Model, glm::vec3(Scale, Scale, 0));
		
		Dirty = false;
	}
	return Model;
}

GLuint Sprite::getTexture()
{
	return Texture;
}
void Sprite::setScale(float scale)
{
	Scale = scale;
	Dirty = true;
}

void Sprite::setTranslation(float x, float y)
{
	X = x;
	Y = y;
	Dirty = true;
}

void Sprite::setRotation(float angle)
{
	Rotation = angle;
	Dirty = true;
}
Sprite::~Sprite(void)
{
}
