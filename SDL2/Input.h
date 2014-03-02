#pragma once
#include "Includes.h"
class Input
{
private:
	glm::vec2 Anchor;
public:
	Input(void);
	void Update(int gameTime);
	void SetPointerAnchor(glm::vec2 anchor);
	float PointerAngle;
	bool Shoot;
	float HorizontalMotion;
	float VerticalMotion;
	bool Quit;
	~Input(void);
};

