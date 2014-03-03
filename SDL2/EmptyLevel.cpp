#include "EmptyLevel.h"


EmptyLevel::EmptyLevel(void)
{
	player = nullptr;
}


EmptyLevel::~EmptyLevel(void)
{
	if(player != nullptr)
	{
		delete player;
	}
}


void EmptyLevel::Initialize(Graphics &g, Input &input)
{
	player = new PlayerShip(&input);
}

void EmptyLevel::CleanUp(Graphics &g)
{
	
	if(player != nullptr)
	{
		delete player;
	}
}

int EmptyLevel::Update(int gameTime)
{
	player->Update(gameTime);
	return 0;
}

void EmptyLevel::Render(Graphics &g)
{
	player->Render(g);
}