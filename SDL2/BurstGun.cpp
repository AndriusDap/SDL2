#include "Includes.h"
#include "BurstGun.h"
#include "GLHelper.h"

BurstGun::BurstGun(function<void(Particle)> BulletStuff):	
	BulletCount(100),
	Bullets(100, Particle(glm::vec2(0), glm::vec2(0), 0, 0)),
	Position(0, 0),
	Speed(1, 1),
	ClipSize(5),
	MaxCooldown(500),
	Clip(5),
	Cooldown(10),
	BulletTexture(0),
	BulletIterator(0),
	BulletLifeTime(100000),
	BulletCraftingTimer(10),
	BulletCraftingCooldown(2 * 1000),
	FanSize(1)
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
		float fanDispersion = 10;
		float fanAngle = angle - (FanSize/2 * fanDispersion);
		
		for(int i = 0; i < FanSize; i++)
		{
			Particle bullet(
					glm::vec2(
						.3 * cos((fanAngle + i * fanDispersion - 90)/ (180 / PI)),
						.3 * sin((fanAngle + i * fanDispersion - 90)/ (180 / PI))
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

void BurstGun::increaseSpeed()
{
	BulletCraftingCooldown = (int) ((double)BulletCraftingCooldown * 0.7);
	if(BulletCraftingCooldown < 10)
	{
		BulletCraftingCooldown = 10;
	}
}

void BurstGun::increaseFanSize()
{
	FanSize++;
}

void BurstGun::decreaseFanSize()
{
	FanSize--;
	if(FanSize == 0)
	{
		FanSize = 1;
	}
}
