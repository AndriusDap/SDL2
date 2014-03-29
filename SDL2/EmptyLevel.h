#pragma once

#include "Includes.h"
#include "ILevel.h"
#include "PlayerShip.h"
#include "StupidBot.h"

class EmptyLevel : public ILevel
{
	std::shared_ptr<PlayerShip> player;
	std::vector<std::shared_ptr<StupidBot>> enemies;
public:
	EmptyLevel(void);
	void Initialize(Graphics &g, Input &input);
	int Update(int gameTime);
	void Render(Graphics &g);
	void CleanUp(Graphics &g);
	~EmptyLevel(void);
};

