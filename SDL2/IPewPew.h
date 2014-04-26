#pragma once
#include "Includes.h"
#include "Graphics.h"
class IPewPew
{
public:
	IPewPew(void){};
	virtual ~IPewPew(void){};
	virtual void setDirection(float angle) = 0;
	virtual void setPosition(glm::vec2 position) = 0;
	virtual void Shoot() = 0;
	virtual void Update(int gameTime) = 0;
	virtual void Render(Graphics &g) = 0;
	virtual void setTexture(GLuint texture) = 0;
	virtual void increaseSpeed() = 0;
};

