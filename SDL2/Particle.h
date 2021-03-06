#pragma once
#include "Includes.h"
#include "IRenderable.h"

class Particle : public IRenderable
{
private:

	
public:
	glm::vec3 Speed;
	glm::mat4 Transformation;
	glm::vec3 Position;	

	float scale;
	Particle(glm::vec2 speed, glm::vec2 position, GLuint texture, int lifeTime);
	glm::mat4 getTransformation();
	GLuint getTexture();
	GLuint Texture;
	int Life;
	void Update(int gameTime);
};

