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
	
	player.reset(new PlayerShip(&input, collider));	
	enemies.emplace_back(new StupidBot(collider));
	collider.AddShip(static_pointer_cast<TriangleCollidable>(player), 0);
	for(auto &e : enemies)
	{
		collider.AddShip(static_pointer_cast<TriangleCollidable>(e), 1);
	}

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
	collider.Update(gameTime);
	return 0;
}

void EmptyLevel::Render(Graphics &g)
{
	player->Render(g);
	for(auto &enemy : enemies)
	{
		enemy->Render(g);
	}
	collider.Render(g);
	//g.Drawtext("M", 100, 100);
}