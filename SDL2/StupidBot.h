#pragma once
#include "IGameEntity.h"
#include "PlayerShip.h"
#include "Collider.h"
#include "TriangleCollidable.h"
class StupidBot : public IGameEntity, public TriangleCollidable
{
	void Spin(int deltaTime);
	void Move(int deltaTime);
	
	std::unique_ptr<IPewPew> Gun;

	glm::vec2 speed;
	glm::vec2 thrust;
	float MaxSpeed;
	float rotation;
	bool IsDead;
	Sprite Ship;
public:
	glm::vec2 position;
	StupidBot(Collider &collider);
	void Render(Graphics &g);
	void Update(int deltaTime);
	
	std::shared_ptr<PlayerShip> target;
	~StupidBot(void);
	
	virtual void Collide(Particle &P);
	virtual bool Dead();
};

