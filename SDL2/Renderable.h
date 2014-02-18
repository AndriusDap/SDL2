#pragma once
#include "Includes.h"

class Renderable
{
private:
	float x;
	float y;
	float rotation;
	float scale;

	int texture;

public:
	Renderable(void);
	virtual ~Renderable(void);
};

