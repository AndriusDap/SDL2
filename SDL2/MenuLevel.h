#pragma once
#include "Includes.h"
#include "ILevel.h"
#include "Input.h"
class MenuLevel : public ILevel
{
private:
	Input* input;
public:
	MenuLevel(void);
	void Initialize(Graphics &g, Input &input);
	int Update(int gameTime);
	void Render(Graphics &g);
	void CleanUp(Graphics &g);
	~MenuLevel(void);
};

