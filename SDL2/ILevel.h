#pragma once
#include "Graphics.h"
#include "Input.h"
class ILevel
{
public:
	ILevel(void);
	virtual void Initialize(Graphics &g, Input &input){};
	virtual int Update(int gameTime) = 0;
	virtual void Render(Graphics &g) = 0;
	virtual void CleanUp(Graphics &g){};
	virtual ~ILevel(void);
};

