#pragma once
#include "Includes.h"
#include "Particle.h"

class TriangleCollidable
{

public:
	float Size;
	glm::vec2 Position;
	TriangleCollidable();
	void SetPosition(glm::vec2 pos);
	bool CheckCollision(Particle &P);
	virtual void Collide(Particle &P){};
	virtual bool Dead(){return false;};
	virtual ~TriangleCollidable(void){};
};

