#pragma once
#include "Includes.h"
#include "Graphics.h"

class IGameEntity
{
public:
	IGameEntity(void){};
	virtual void Render(Graphics &g){};
	virtual void Update(int deltaTime){};
	virtual ~IGameEntity(void){};
};

