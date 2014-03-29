#include "Includes.h"
#include "Input.h"
using namespace std;

Input::Input(void):Anchor(SCREEN_WIDTH/2, SCREEN_HEIGHT/2)
{
	PointerAngle = 0;
	Shoot = false;
	HorizontalMotion = 0.0f;
	VerticalMotion = 0.0f;
	Quit = false;
}

void Input::SetPointerAnchor(glm::vec2 anchor)
{
	Anchor = anchor;
}

void Input::Update(int gameTime)
{
	
	PointerAngle = 0;
	Shoot = false;
	HorizontalMotion = 0.0f;
	VerticalMotion = 0.0f;

	int x, y;
	auto buttons = SDL_GetMouseState(&x, &y);
	MousePosition[0] = x;
	MousePosition[1] = y;
	y = SCREEN_HEIGHT - y;
	PointerAngle = (float) ( 180 - atan2((float)(x - Anchor.x),(float)(y - Anchor.y)) * 180 / 3.14159265);
	Shoot = buttons & SDL_BUTTON(1);
	
	SDL_PumpEvents();
	auto keyboard = SDL_GetKeyboardState(NULL);
	if(keyboard[SDL_SCANCODE_ESCAPE])
	{
		//Quit = true;
	}

	if(keyboard[SDL_SCANCODE_W])
	{
		VerticalMotion = 1.0f;
	}
	
	if(keyboard[SDL_SCANCODE_S])
	{
		VerticalMotion = -1.0f;
	}

	if(keyboard[SDL_SCANCODE_A])
	{
		HorizontalMotion = -1.0f;
	}

	if(keyboard[SDL_SCANCODE_D])
	{
		HorizontalMotion = 1.0f;
	}

	SDL_Event Event;
	while(SDL_PollEvent(&Event))
	{
		if(Event.type == SDL_QUIT)
		{
			Quit = true;
		}
	}	
}

Input::~Input(void)
{
}
