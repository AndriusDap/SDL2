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
	glm::vec2 default_direction;
	glm::vec2 speed;
	glm::vec2 thrust;
	float MaxSpeed;
	float rotation;
	bool IsDead;
	Sprite Ship;
	glm::vec2 MoveTarget;
	

public:
	glm::vec2 position;
	StupidBot(Collider &collider);
	void Render(Graphics &g);
	void Update(int deltaTime);
	void MoveTo(glm::vec2 pos);
	std::shared_ptr<PlayerShip> target;
	~StupidBot(void);
	std::function<void(glm::vec2)> OnDeath;
	virtual void Collide(Particle &P);
	virtual bool Dead();
};

