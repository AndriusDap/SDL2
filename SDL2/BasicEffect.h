#pragma once
#include "Includes.h"

class BasicEffect
{
private:
	GLuint Program;
	GLuint FragmentShader;
	GLuint VertexShader;

	GLuint ModelHandle;
	GLuint ViewHandle;
	GLuint ProjectionHandle;

public:
	BasicEffect(void);

	void begin();

	void setModel(glm::mat4 Model);

	void setProjection(glm::mat4 Projection);
	void setView(glm::mat4 View);

	void end();

	~BasicEffect(void);
};

