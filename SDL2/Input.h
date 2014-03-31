#pragma once
#include "Includes.h"
class Input
{
private:
	glm::vec2 Anchor;
	GLFWwindow *window;
public:
	Input(GLFWwindow *Window);
	void Update(int gameTime);
	void SetPointerAnchor(glm::vec2 anchor);
	int MousePosition[2];
	float PointerAngle;
	bool Shoot;
	float HorizontalMotion;
	float VerticalMotion;
	bool Quit;
	~Input(void);
};

