#pragma once
#include "Includes.h"
class IRenderable
{
public:
	virtual glm::mat4 getTransformation(){ return glm::mat4(1); };
	virtual ~IRenderable(){};
	virtual GLuint getTexture(){ return 0; };
	GLuint Texture;
};