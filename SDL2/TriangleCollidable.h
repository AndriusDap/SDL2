#pragma once
#include "Includes.h"
#include "Particle.h"

class TriangleCollidable
{
vector<double> Vertices;
public:
	TriangleCollidable();
	void SetTriangle(double triangle[6]);

	bool CheckCollision(Particle &P);
	virtual void Collide(Particle &P){};
	virtual bool Dead(){ cout << "fuck" << endl; return false;};
	virtual ~TriangleCollidable(void){};
};

