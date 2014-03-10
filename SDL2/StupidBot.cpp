#include "StupidBot.h"
#include "GLHelper.h"
#include "BurstGun.h"
#include <iostream>
StupidBot::StupidBot():
	position(500, 500),
	target(nullptr),
	rotation(0),
	Ship(),
	Gun(new BurstGun())
{
	Gun->setTexture(GLHelper::LoadTexture("EnemyBullet.png"));
	Ship.Texture = GLHelper::LoadTexture("Enemy.png");
	Ship.setScale(100);
	Ship.setRotation(90);	
}



void StupidBot::Spin(int deltaTime)
{
	glm::vec2 direction = target->position;
	rotation = (float) (180 - atan2((float)(direction.x - position.x),(float)(direction.y - position.y)) * 180 / 3.14159265);
	
	rotation = fmod(rotation, 360);
}

void StupidBot::Move(int deltaTime)
{
	glm::vec2 direction = glm::vec2(
					 0.5 * cos((rotation - 90)/ (180 / PI)),
					 0.5 * sin((rotation - 90)/ (180 / PI))
					);
	double dist = glm::distance(position, target->position);
	if(dist > 300)
	{
		position += direction * (float) deltaTime;
	}
}

void StupidBot::Render(Graphics &g)
{
	Ship.setRotation(rotation);
	Ship.setTranslation(position.x, position.y);
	g.Render(Ship);

	Gun->Render(g);
}

void StupidBot::Update(int deltaTime)
{
	Move(deltaTime);
	Spin(deltaTime);
	Gun->setDirection(rotation);
	Gun->Shoot();
	Gun->setPosition(position + glm::vec2(
					50 * cos((rotation - 90)/ (180 / PI)),
					50 * sin((rotation - 90)/ (180 / PI))
					));
	Gun->Update(deltaTime);
}

StupidBot::~StupidBot()
{

}