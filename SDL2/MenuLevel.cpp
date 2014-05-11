#include "Includes.h"
#include "MenuLevel.h"


MenuLevel::MenuLevel(void)
{
}

void MenuLevel::Initialize(Graphics &g, Input &input)
{
	this->input = &input;
}

int MenuLevel::Update(int gameTime)
{
	return 0;
}

void MenuLevel::Render(Graphics &g)
{
	
}

void MenuLevel::CleanUp(Graphics &g)
{
	
}

MenuLevel::~MenuLevel(void)
{
}
