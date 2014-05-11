#pragma once
#include "Includes.h"
#include "Input.h"
#include "IGameEntity.h"

class Button : public IGameEntity
{
public:
	Button(Input &input, string text);	
	void Render(Graphics &g);
	void Update(int deltaTime);
	~Button(void);
};

