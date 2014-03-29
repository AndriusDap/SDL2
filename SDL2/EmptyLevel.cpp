#include "Includes.h"
#include "EmptyLevel.h"


EmptyLevel::EmptyLevel(void)
{
}


EmptyLevel::~EmptyLevel(void)
{

}


void EmptyLevel::Initialize(Graphics &g, Input &input)
{
	player.reset(new PlayerShip(&input));
	enemies.emplace_back(new StupidBot());
	enemies[0]->target = player;
}

void EmptyLevel::CleanUp(Graphics &g)
{
}

int EmptyLevel::Update(int gameTime)
{
	player->Update(gameTime);
	for(auto &enemy : enemies)
	{
		enemy->Update(gameTime);
	}
	return 0;
}

void EmptyLevel::Render(Graphics &g)
{
	player->Render(g);
	for(auto &enemy : enemies)
	{
		enemy->Render(g);
	}
	g.Drawtext("M", 100, 100);
}