#include "Includes.h"
#include "Collider.h"


Collider::Collider(void)
{
}


Collider::~Collider(void)
{
}	

void Collider::Render(Graphics &g)
{
	for(int i = 0; i < 10; i++)
	{
		for(auto &p : Particles[i])
		{
			g.Render(p);
		}
	}
}

void Collider::Update(int deltaTime)
{
	for(int i = 0; i < 10; i++)
	{
		for(auto &p : Particles[i])
		{
			if(p.Life > 0){
				p.Update(deltaTime);
				for(auto &s : Ships[i])
				{
					if(s->CheckCollision(p))
					{
						s->Collide(p);
						p.Life = 0;
						break;
					}
				}
			}
		}

		auto dead_guys = remove_if(Particles[i].begin(), Particles[i].end(), [](Particle p){return p.Life <= 0;});
		Particles[i].erase(dead_guys, Particles[i].end());
		auto dead_ships = remove_if(Ships[i].begin(), Ships[i].end(), [](shared_ptr<TriangleCollidable> ship){return ship->Dead();});
		Ships[i].erase(dead_ships, Ships[i].end());
	}

}
	
void Collider::AddBullet(Particle P, int collisionLevel)
{
	Particles[collisionLevel].push_back(P);
}

void Collider::AddShip(shared_ptr<TriangleCollidable> collidable, int collisionLevel)
{
	Ships[collisionLevel].push_back(collidable);
}