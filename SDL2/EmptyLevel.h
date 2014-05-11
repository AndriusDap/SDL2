#pragma once
#include "Includes.h"
#include "ILevel.h"
#include "PlayerShip.h"
#include "StupidBot.h"
#include "Collider.h"
#include "Pickups.h"

class EmptyLevel : public ILevel
{
	std::shared_ptr<PlayerShip> player;
	std::vector<std::shared_ptr<StupidBot>> enemies;
	std::shared_ptr<Pickups> pickups;
	Collider collider;
	int score;
public:
	EmptyLevel(void);
	void Initialize(Graphics &g, Input &input);
	int Update(int gameTime);
	void Render(Graphics &g);
	void CleanUp(Graphics &g);
	~EmptyLevel(void);
};

