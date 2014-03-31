#include "Includes.h"
#include "BasicEffect.h"
#include "GLHelper.h"

BasicEffect::BasicEffect(void)
{
	
}

void BasicEffect::init()
{
	FragmentShader = GLHelper::LoadShader("Assets/fragmentShader.glsl", GL_FRAGMENT_SHADER);
	VertexShader = GLHelper::LoadShader("Assets/vertexShader.glsl", GL_VERTEX_SHADER);
	Program = GLHelper::CreateProgram(FragmentShader, VertexShader);

	// Get fields:
	ModelHandle = glGetUniformLocation(Program, "Model");
	ViewHandle = glGetUniformLocation(Program, "View");
	ProjectionHandle = glGetUniformLocation(Program, "Projection");
	TextureHandle = glGetUniformLocation(Program, "TextureSampler");
	CheckGlErrors();
}

void BasicEffect::setModel(glm::mat4 Model)
{
	glUniformMatrix4fv(ModelHandle, 1, 0, &Model[0][0]);
}

void BasicEffect::setProjection(glm::mat4 Projection)
{
	glUniformMatrix4fv(ProjectionHandle, 1, 0, &Projection[0][0]);
}

void BasicEffect::setView(glm::mat4 View)
{
	glUniformMatrix4fv(ViewHandle, 1, 0, &View[0][0]);
}

void BasicEffect::setTexture(GLuint Texture)
{
	glUniform1i(TextureHandle, Texture);
}

void BasicEffect::begin()
{
	glUseProgram(Program);
}

void BasicEffect::end()
{

}

BasicEffect::~BasicEffect(void)
{
	glDeleteShader(FragmentShader);
	glDeleteShader(VertexShader);
	glDeleteProgram(Program);
}
