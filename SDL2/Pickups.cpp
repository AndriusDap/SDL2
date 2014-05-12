#include "Includes.h"
#include "Pickups.h"
#include "BurstGun.h"

Pickups::Pickups(shared_ptr<PlayerShip> player) : player(player)
{
}


void Pickups::SpawnIfLucky(glm::vec2 position)
{
	int rnd = rand() % 10;
	bool lucky = rnd < 5;
	if(lucky)
	{
		Sprite pickup;
		pickup.setScale(50);
		pickup.setTranslation(position.x, position.y);
		if(rand()%2)
		{
			pickup.Texture = GLHelper::LoadTexture("Assets/plus.png");
		}
		else
		{
			pickup.Texture = GLHelper::LoadTexture("Assets/redPlus.png");
		}
		activePickups.emplace_back(pickup);	
	}
}

void Pickups::Render(Graphics &g)
{
	for(auto &pickup : activePickups)
	{

		g.Render(pickup);
	}
}


void Pickups::Update(int deltaTime)
{
	glm::vec2 playerPosition = player->Position;
	for(int i = activePickups.size()-1; i >= 0; i--)
	{
		if(glm::distance(playerPosition, glm::vec2(activePickups[i].X, activePickups[i].Y)) < 30 )
		{
			if(activePickups[i].getTexture() == GLHelper::LoadTexture("Assets/plus.png"))
			{
				player->Gun->increaseSpeed();
			
				((BurstGun*) player->Gun.get())->increaseFanSize();
			}
			else
			{
				((BurstGun*) player->Gun.get())->decreaseFanSize();
			}
			activePickups.erase(activePickups.begin() + i);
		}		
	}

	for(auto &pickup : activePickups)
	{
		pickup.setRotation(pickup.Rotation + deltaTime * 0.01f);
	}
}

Pickups::~Pickups(void)
{
}
