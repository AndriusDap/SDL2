#pragma once
#include "Includes.h"
#include "IGameEntity.h"
#include "Graphics.h"
#include "PlayerShip.h"
#include "GLHelper.h"

class Pickups : IGameEntity
{
	vector<Sprite> activePickups;
	shared_ptr<PlayerShip> player;
public:
	Pickups(shared_ptr<PlayerShip> player);
	void SpawnIfLucky(glm::vec2 position);
	virtual void Render(Graphics &g);
	virtual void Update(int deltaTime);
	~Pickups(void);
};

