#include "PlayerShip.h"
#include <cmath>
#include <iostream>
#include "GLHelper.h"
#include "BurstGun.h"
using namespace std;

PlayerShip::PlayerShip(Input* Input): position(300, 300), speed(0, 0), thrust(0.01, 0.01), Gun(new BurstGun())
{
	MaxSpeed = 0.8;
	Mass = 0.1;
	Ship.setScale(100);
	Ship.setRotation(90);
	input = Input;
	Ship.Texture = GLHelper::LoadTexture("Ship.png");
}


PlayerShip::~PlayerShip()
{
}

void PlayerShip::Spin(int deltaTime)
{
	rotation = input->PointerAngle;
}

void PlayerShip::Move(int deltaTime)
{
	glm::vec2 acceleration(
			(input->HorizontalMotion * thrust.x) / Mass, 
			(input->VerticalMotion * thrust.y) / Mass );
	speed += acceleration * (float) deltaTime;

	if(speed.x > MaxSpeed)
	{
		speed.x = (float) MaxSpeed;
	}
	if(speed.y > MaxSpeed)
	{
		speed.y = (float) MaxSpeed;
	}

	if(speed.x < -MaxSpeed)
	{
		speed.x = (float) -MaxSpeed;
	}
	if(speed.y < -MaxSpeed)
	{
		speed.y = (float) -MaxSpeed;
	}

	position += speed * (float)deltaTime;

	while(position.x < 0)
	{
		position.x += SCREEN_WIDTH;
	}

	while(position.y < 0)
	{
		position.y += SCREEN_HEIGHT;
	}

	position.x = fmod(position.x, (float) SCREEN_WIDTH);
	position.y = fmod(position.y, (float) SCREEN_HEIGHT);
	
	speed *= (float) ( 1 - 0.05 * deltaTime);
}

void PlayerShip::Render(Graphics &g)
{
	Ship.setRotation(rotation);
	Ship.setTranslation(position.x, position.y);
	g.Render(Ship);

	Gun->Render(g);
}

void PlayerShip::Update(int deltaTime)
{

	Move(deltaTime);
	Spin(deltaTime);
	Gun->setPosition(
		position + glm::vec2(
					50 * cos((rotation - 90)/ (180 / PI)),
					50 * sin((rotation - 90)/ (180 / PI))
					));
	Gun->setDirection(rotation);
	Gun->Update(deltaTime);
	if(input->Shoot)
	{
		Gun->Shoot();
	}
	input->SetPointerAnchor(position);
}