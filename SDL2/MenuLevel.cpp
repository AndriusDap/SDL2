#include "Includes.h"
#include "MenuLevel.h"
#include "GLHelper.h"



MenuLevel::MenuLevel(void)
{
}

void MenuLevel::Initialize(Graphics &g, Input &input)
{
	this->input = &input;
	this->input->text_buffer = "";
}

int MenuLevel::Update(int gameTime)
{
	if(input->Shoot) 
	{
		return 1;
	}
	return 0;
}

void MenuLevel::Render(Graphics &g)
{
	int lastScore = GLHelper::GetLastScore();
	if(lastScore != -1)
	{
		g.RenderText(200, 500, "Enter your name: " + input->text_buffer);
		g.RenderText(200, 450, "You died. Your score: " + to_string(lastScore));
	}
	g.RenderText(200, 300, "Press lmb to start");
	g.RenderText(200, 350, "Highscore: " + GLHelper::GetHighscore());
}

void MenuLevel::CleanUp(Graphics &g)
{
	GLHelper::SetHighscore(GLHelper::GetLastScore(), input->text_buffer);
}

MenuLevel::~MenuLevel(void)
{
}
