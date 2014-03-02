#pragma once
#include "IPewPew.h"
#include "Particle.h"
#include "Sprite.h"
#include <vector>
using namespace std;

class BurstGun : public IPewPew
{
	glm::vec2 Position;
	vector<Particle> Bullets;
	int ClipSize;
	int MaxCooldown;
	int Clip;
	int BulletCraftingTimer;
	int BulletCraftingCooldown;
	int Cooldown;
	int BulletCount;
	int BulletIterator;
	float angle;
	int BulletLifeTime;
	GLuint BulletTexture;
	glm::vec2 Speed;

	Sprite ClipPreview;
public:
	BurstGun(void);
	~BurstGun(void);
	void setDirection(float angle);
	void setPosition(glm::vec2 position);
	void Shoot();
	void Update(int gameTime);
	void Render(Graphics &g);
};
