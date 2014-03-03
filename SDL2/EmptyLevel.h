#pragma once
#include "ILevel.h"
#include "Includes.h"
#include "PlayerShip.h"

class EmptyLevel : public ILevel
{
	PlayerShip* player;

public:
	EmptyLevel(void);
	void Initialize(Graphics &g, Input &input);
	int Update(int gameTime);
	void Render(Graphics &g);
	void CleanUp(Graphics &g);
	~EmptyLevel(void);
};

