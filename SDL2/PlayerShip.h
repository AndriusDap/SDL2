#pragma once
#include "Includes.h"
#include "Particle.h"
#include "Sprite.h"
#include "IGameEntity.h"
#include "Input.h"
#include "IPewPew.h"
#include "Collider.h"

class PlayerShip : public IGameEntity, public TriangleCollidable
{	
private:
	
	glm::vec2 speed;
	glm::vec2 thrust;
	
	float rotation;
	Input* input;
	double MaxSpeed;
	double Mass;

	void Spin(int deltaTime);
	void Move(int deltaTime);
	std::unique_ptr<IPewPew> Gun;

	
public:
	PlayerShip(Input *Input, Collider &collider);
	~PlayerShip(void);
	Sprite Ship;
	glm::vec2 position;

	void Render(Graphics &g);
	void Update(int deltaTime);
	
	virtual void Collide(Particle &P);
	virtual bool Dead();
};

