#pragma once
#include "Includes.h"
#include "IGameEntity.h"
#include "Particle.h"
#include "TriangleCollidable.h"

class Collider : IGameEntity
{
	vector<Particle> Particles[10];
	vector<shared_ptr<TriangleCollidable>> Ships[10];
public:
	Collider(void);
	~Collider(void);
	
	virtual void Render(Graphics &g);
	virtual void Update(int deltaTime);
	
	void AddBullet(Particle P, int collisionLevel);
	void AddShip(shared_ptr<TriangleCollidable> collidable, int collisionLevel);
};

