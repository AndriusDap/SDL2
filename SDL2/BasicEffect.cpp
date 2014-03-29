#include "Includes.h"
#include "BasicEffect.h"
#include "GLHelper.h"

BasicEffect::BasicEffect(void)
{
	
}

void BasicEffect::init()
{
	FragmentShader = GLHelper::LoadShader("Assets/fragmentShader.glsl", gl::FRAGMENT_SHADER);
	VertexShader = GLHelper::LoadShader("Assets/vertexShader.glsl", gl::VERTEX_SHADER);
	Program = GLHelper::CreateProgram(FragmentShader, VertexShader);

	// Get fields:
	ModelHandle = gl::GetUniformLocation(Program, "Model");
	ViewHandle = gl::GetUniformLocation(Program, "View");
	ProjectionHandle = gl::GetUniformLocation(Program, "Projection");
	TextureHandle = gl::GetUniformLocation(Program, "TextureSampler");
	CheckGlErrors();
}

void BasicEffect::setModel(glm::mat4 Model)
{
	gl::UniformMatrix4fv(ModelHandle, 1, 0, &Model[0][0]);
}

void BasicEffect::setProjection(glm::mat4 Projection)
{
	gl::UniformMatrix4fv(ProjectionHandle, 1, 0, &Projection[0][0]);
}

void BasicEffect::setView(glm::mat4 View)
{
	gl::UniformMatrix4fv(ViewHandle, 1, 0, &View[0][0]);
}

void BasicEffect::setTexture(GLuint Texture)
{
	gl::Uniform1i(TextureHandle, Texture);
}

void BasicEffect::begin()
{
	gl::UseProgram(Program);
}

void BasicEffect::end()
{

}

BasicEffect::~BasicEffect(void)
{
	gl::DeleteShader(FragmentShader);
	gl::DeleteShader(VertexShader);
	gl::DeleteProgram(Program);
}
