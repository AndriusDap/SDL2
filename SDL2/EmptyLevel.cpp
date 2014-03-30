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

	collider.Update(gameTime);
	size_t spanws_count = spawns.size();
	if(spanws_count != 0)
	{
		cout << "Spawn " << spanws_count << "Total count" << enemies.size() << endl;
		enemies.insert(enemies.end(), spawns.begin(), spawns.begin() + 2);
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
	collider.Render(g);
	//g.Drawtext("M", 100, 100);
}