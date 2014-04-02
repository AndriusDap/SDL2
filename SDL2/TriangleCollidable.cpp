#include "Includes.h"
#include "TriangleCollidable.h"


TriangleCollidable::TriangleCollidable(void)
{
	Size = 20;
}

bool TriangleCollidable::CheckCollision(Particle &P)
{

	//http://stackoverflow.com/questions/2049582/how-to-determine-a-point-in-a-triangle
	auto p0x = Position.x;
	auto p0y = Position.y;
	double dist = sqrt((p0x - P.Position.x) * (p0x - P.Position.x) + (p0y - P.Position.y) * (p0y - P.Position.y));
	return dist < Size;
}

void TriangleCollidable::SetPosition(glm::vec2 pos)
{
	Position = pos;
}