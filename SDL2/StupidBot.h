#pragma once
#include "IGameEntity.h"
#include "PlayerShip.h"
#include <memory>

class StupidBot : IGameEntity
{
	void Spin(int deltaTime);
	void Move(int deltaTime);
	
	std::unique_ptr<IPewPew> Gun;
	glm::vec2 position;
	glm::vec2 speed;
	glm::vec2 thrust;
	float MaxSpeed;
	float rotation;
	
	Sprite Ship;
public:
	StupidBot(void);
	void Render(Graphics &g);
	void Update(int deltaTime);
	
	std::shared_ptr<PlayerShip> target;
	~StupidBot(void);
};

