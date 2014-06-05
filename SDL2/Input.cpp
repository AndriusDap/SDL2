#include "Includes.h"
#include "Input.h"
using namespace std;

Input::Input(GLFWwindow *Window):Anchor(SCREEN_WIDTH/2, SCREEN_HEIGHT/2)
{
	window = Window;
	PointerAngle = 0;
	Shoot = false;
	HorizontalMotion = 0.0f;
	VerticalMotion = 0.0f;
	Quit = false;
	for(int i = 0; i < 100; i++)
	{
		presed_keys[i] = false;
	}
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
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	x = (int) floor(xpos);
	y = (int) floor(ypos);
	
	MousePosition[0] = x;
	MousePosition[1] = y;
	y = SCREEN_HEIGHT - y;
	PointerAngle = (float) ( 180 - atan2((float)(x - Anchor.x),(float)(y - Anchor.y)) * 180 / 3.14159265);
	Shoot = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS;
	

	if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		VerticalMotion = 1.0f;
	}
	
	if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		VerticalMotion = -1.0f;
	}

	if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		HorizontalMotion = -1.0f;
	}

	if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		HorizontalMotion = 1.0f;
	}

	for(int i = 65; i < 91; i++)
	{
		if(glfwGetKey(window, i) == GLFW_PRESS)
		{
			if(!presed_keys[i]) 
			{
				text_buffer += (char) i;
				presed_keys[i] = true;
			}
		}
		else
		{
			presed_keys[i] = false;
		}
	}

	if(glfwGetKey(window, GLFW_KEY_BACKSPACE) == GLFW_PRESS)
	{
		text_buffer = text_buffer.length() == 1 ? "" : text_buffer.substr(0, text_buffer.length() - 1);
	}

	Quit = glfwWindowShouldClose(window) == 1? true : false;
}

Input::~Input(void)
{
}
