#include "Particle.h"

Particle::Particle(glm::vec2 speed, glm::vec2 position, GLuint texture, int lifeTime)
{
	Speed = glm::vec3(speed.x, speed.y, 0);
	Transformation = glm::translate(glm::mat4(1), glm::vec3(position, 0));
	Transformation = glm::scale(Transformation, glm::vec3(30, 30, 1));
	Life = lifeTime;
	Texture = texture;
	Position = glm::vec3(position, 0);
}

glm::mat4 Particle::getTransformation()
{
	return Transformation;
}
GLuint Particle::getTexture()
{
	return Texture;
}
void Particle::Update(int gameTime)
{
	if(Life >= 0)
	{
		Position += Speed * (float) gameTime;
		Transformation = glm::translate(glm::mat4(1), Position);
		Transformation = glm::scale(Transformation, glm::vec3(30, 30, 1));
		Life -= gameTime;
		if(Position.y < 0 ||
			Position.x < 0 ||
			Position.x > SCREEN_WIDTH ||
			Position.y > SCREEN_HEIGHT)
			Life = 0;
	}
}