#pragma once
#include <vector>
#include <memory>

#include "Particle.h"
#include "Sprite.h"
#include "IGameEntity.h"
#include "Input.h"
#include "IPewPew.h"

class PlayerShip : IGameEntity
{	
private:
	glm::vec2 position;
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
	PlayerShip(Input *Input);
	~PlayerShip(void);
	Sprite Ship;

	void Render(Graphics &g);
	void Update(int deltaTime);
};

