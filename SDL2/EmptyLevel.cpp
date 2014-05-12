#include "Includes.h"
#include "EmptyLevel.h"
#include "MasterMind.h"

EmptyLevel::EmptyLevel(void)
{
}


EmptyLevel::~EmptyLevel(void)
{

}


void EmptyLevel::Initialize(Graphics &g, Input &input)
{
	score = 0;
	player.reset(new PlayerShip(&input, collider));	
	pickups.reset(new Pickups(player));
	enemies.emplace_back(new StupidBot(collider));
	collider.AddShip(static_pointer_cast<TriangleCollidable>(player), 0);
	for(auto &e : enemies)
	{
		collider.AddShip(static_pointer_cast<TriangleCollidable>(e), 1);
	}

	enemies[0]->target = player;
	enemies[0]->OnDeath = [&](glm::vec2 position) {pickups->SpawnIfLucky(position); score += 10;};
}

void EmptyLevel::CleanUp(Graphics &g)
{
}

int EmptyLevel::Update(int gameTime)
{

	MasterMind::MoveBots(enemies, player->position);

	for(auto &enemy : enemies)
	{
		enemy->Update(gameTime);
	}
	collider.Update(gameTime);
	
	vector<shared_ptr<StupidBot>> spawns;
	for(auto &enemy : enemies)
	{
		if(enemy->Dead())
		{
			auto vect = enemy->position - player->position;
			vect = glm::normalize(vect);
			vect = vect * 200.0f;
			vect = glm::vec2(vect.y, -vect.x);

			shared_ptr<StupidBot> first(new StupidBot(collider));
			first->position = enemy->position + vect;
			first->target = player;
			shared_ptr<StupidBot> second(new StupidBot(collider));
			first->OnDeath = [&](glm::vec2 position) {pickups->SpawnIfLucky(position); score += 10;};
			second->OnDeath = [&](glm::vec2 position) {pickups->SpawnIfLucky(position); score += 10;};
			second->position = enemy->position - vect;
			second->target = player;
			spawns.emplace_back(first);
			spawns.emplace_back(second);
			collider.AddShip(static_pointer_cast<TriangleCollidable>(first), 1);
			collider.AddShip(static_pointer_cast<TriangleCollidable>(second), 1);
		}
	}

	
	auto deadguys = remove_if(enemies.begin(), enemies.end(), [](shared_ptr<StupidBot> enemy){return enemy->Dead();});
	enemies.erase(deadguys, enemies.end());

	pickups->Update(gameTime);
	player->Update(gameTime);


	size_t spanws_count = spawns.size();
	if(spanws_count != 0)
	{
		enemies.insert(enemies.end(), spawns.begin(), spawns.end());
	}
	if(player->Dead())
	{
		GLHelper::SetHighscore(score);
		return 1;
	}
	else
	{
		return 0;
	}
}

void EmptyLevel::Render(Graphics &g)
{
	pickups->Render(g);
	player->Render(g);
	for(auto &enemy : enemies)
	{
		enemy->Render(g);
	}
	collider.Render(g);
	g.RenderText(800, 600, "Score: " + to_string(score));
	//g.Drawtext("M", 100, 100);
}