#include "Includes.h"
#include "TriangleCollidable.h"


TriangleCollidable::TriangleCollidable(void)
{
}

void TriangleCollidable::SetTriangle(double triangle[6])
{
	Vertices.clear();
	Vertices.emplace_back(triangle[0]);
	Vertices.emplace_back(triangle[1]);
	Vertices.emplace_back(triangle[2]);
	Vertices.emplace_back(triangle[3]);
	Vertices.emplace_back(triangle[4]);
	Vertices.emplace_back(triangle[5]);
}

bool TriangleCollidable::CheckCollision(Particle &P)
{

	//http://stackoverflow.com/questions/2049582/how-to-determine-a-point-in-a-triangle
	auto p0x = Vertices[0];
	auto p0y = Vertices[1];
	double dist = sqrt((p0x - P.Position.x) * (p0x - P.Position.x) + (p0y - P.Position.y) * (p0y - P.Position.y));
	return dist < 20;
	/*auto p1x = Vertices[2];
	auto p1y = Vertices[3];
	auto p2x = Vertices[4];
	auto p2y = Vertices[5];

	double px = P.Position.x;
	double py = P.Position.y;

	auto Area = 1/2*(-p1y*p2x + p0y*(-p1x + p2x) + p0x*(p1y - p2y) + p1x*p2y);
	auto s = 1/(2*Area)*(p0y*p2x - p0x*p2y + (p2y - p0y)*px + (p0x - p2x)*py);
	auto t = 1/(2*Area)*(p0x*p1y - p0y*p1x + (p0y - p1y)*px + (p1x - p0x)*py);
	
	bool result = s > 0 && t > 0 && (1 - s - t) > 0;
	return result;*/
}