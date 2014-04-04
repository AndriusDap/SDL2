#include "Includes.h"
#include "BurstGun.h"
#include "GLHelper.h"

BurstGun::BurstGun(function<void(Particle)> BulletStuff):	
	BulletCount(100),
	Bullets(100, Particle(glm::vec2(0), glm::vec2(0), 0, 0)),
	Position(0, 0),
	Speed(1, 1),
	ClipSize(5),
	MaxCooldown(50),
	Clip(5),
	Cooldown(0),
	BulletTexture(0),
	BulletIterator(0),
	BulletLifeTime(1000),
	BulletCraftingTimer(0),
	BulletCraftingCooldown(2 * 300)
{
	BulletTexture = GLHelper::LoadTexture("Assets/Bullet.png");
	ClipPreview.Texture = BulletTexture;
	ClipPreview.setRotation(0);
	BulletTarget = BulletStuff;
}


BurstGun::~BurstGun(void)
{
}

void BurstGun::setPosition(glm::vec2 position)
{
	Position = position;
	ClipPreview.setTranslation(position.x, position.y);
}

void BurstGun::setDirection(float direction)
{
	angle = direction;
}

void BurstGun::Shoot()
{
	if(Cooldown <= 0 && Clip > 0)
	{
		Clip--;
		Particle bullet(
				glm::vec2(
					1 * cos((angle - 90)/ (180 / PI)),
					1 * sin((angle - 90)/ (180 / PI))
					),
				Position,
				BulletTexture,
				BulletLifeTime
				);
		bullet.scale = (float) max((Clip + 1) * 8, 3 * 8);
		BulletTarget(bullet);
		Cooldown = MaxCooldown;
	}
}

void BurstGun::setTexture(GLuint texture)
{
	BulletTexture = texture;
}

void BurstGun::Update(int gameTime)
{
	BulletCraftingTimer += gameTime;
	while(BulletCraftingTimer >= BulletCraftingCooldown && Clip < ClipSize)
	{
		Clip++;
		BulletCraftingTimer -= BulletCraftingCooldown;		
	}

	BulletCraftingTimer %= BulletCraftingCooldown;
	
	ClipPreview.setScale((float) Clip * 8);

	if(Cooldown > 0)
	{
		Cooldown -= gameTime;
	}

	for(auto &bullet : Bullets)
	{
		bullet.Update(gameTime);
	}
}

void BurstGun::Render(Graphics &g)
{
	g.Render(ClipPreview);
	for(auto &bullet : Bullets)
	{
		if(bullet.Life > 0)
		{
			g.Render(bullet);
		}
	}
}