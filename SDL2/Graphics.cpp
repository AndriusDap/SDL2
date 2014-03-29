#include "Includes.h"
#include "Graphics.h"

Graphics::Graphics(int w, int h)
{

	if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
		exit(-1);
	}

	if(SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4)){
		std::cout << "Cannot get major version" << std::endl;
	}
	if(SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3)){
		std::cout << "Cannot get minor version" << std::endl;
	}
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
	main_window = SDL_CreateWindow("OPENGL", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	
	
	main_context = SDL_GL_CreateContext(main_window);
	
	glload::LoadFunctions();
	
	gl::Disable(gl::DEPTH_TEST);
	gl::DepthFunc(gl::LESS);
	gl::Enable(gl::MULTISAMPLE);
	gl::BlendFunc(gl::SRC_ALPHA, gl::ONE_MINUS_SRC_ALPHA);
	gl::Enable(gl::BLEND);
	ProjectionMatrix = glm::ortho((float) 0, (float) w, (float) 0, (float) h, (float) 0.01, (float) 100);
	
	ViewMatrix = glm::lookAt(
		glm::vec3(0, 0, 3), // Camera location
		glm::vec3(0, 0, 0), // Camera is directed to screen center
		glm::vec3(0, 1, 0)  // Head is up
	);
	
	Text = new TextFactory();

	Shader.init();
	InitializeRectangle();
	StartRendering();

	//gl::ClearColor(0.8f, 0.8f, 0.8f, 1.0);
}

void Graphics::StartRendering()
{
	gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);
	
	Shader.begin();
	Shader.setProjection(ProjectionMatrix);
	Shader.setView(ViewMatrix);
	
	gl::EnableVertexAttribArray(0);		
	gl::BindBuffer(gl::ARRAY_BUFFER, SquareVBO);	
	gl::EnableVertexAttribArray(1);
	gl::BindBuffer(gl::ARRAY_BUFFER, SquareUV);
	CheckGlErrors();
}

void Graphics::Flip()
{	
	gl::DisableVertexAttribArray(0);
	gl::DisableVertexAttribArray(1);
	Shader.end();

	Text->Render(ProjectionMatrix);

	SDL_GL_SwapWindow(main_window);

	gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);
	
	Shader.begin();
	Shader.setProjection(ProjectionMatrix);
	Shader.setView(ViewMatrix);
	
	gl::EnableVertexAttribArray(0);		
	gl::BindBuffer(gl::ARRAY_BUFFER, SquareVBO);	
	gl::EnableVertexAttribArray(1);
	gl::BindBuffer(gl::ARRAY_BUFFER, SquareUV);	
	LastTexture = 0;
	CheckGlErrors();
}

glm::mat4 Graphics::Projection()
{
	return ProjectionMatrix;
}


void Graphics::Render(IRenderable &renderable)
{
	Shader.setModel(renderable.getTransformation());
	GLuint texture = renderable.getTexture();
	if(LastTexture != texture)
	{
		gl::ActiveTexture(gl::TEXTURE0);
		gl::BindTexture(gl::TEXTURE_2D, texture);
		Shader.setTexture(0);
		LastTexture = texture;
	}
	
	gl::DrawArrays(gl::TRIANGLES, 0, 6);		
	CheckGlErrors();
}


Graphics::~Graphics(void)
{
	delete Text;
	SDL_GL_DeleteContext(main_context);
	SDL_DestroyWindow(main_window);

	SDL_Quit();
}

void Graphics::InitializeRectangle()
{
	float SquareCoordinateArray[] = {
		
		 0.5f, 0.5f, 0.0f,
		 -0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f, 0.5f, 0.0f,
		 -0.5f, 0.5f, 0.0f,
		 -0.5f, -0.5f, 0.0f,
	};
	float UV[] = {
		1.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,
	};

	SquareVBO;
	// Generate new VBO and store it at SquareVBO
	gl::GenBuffers(1, &SquareVBO);

	// Make it active
	gl::BindBuffer(gl::ARRAY_BUFFER, SquareVBO);

	// Upload vertex data to gpu
	gl::BufferData(gl::ARRAY_BUFFER, sizeof(SquareCoordinateArray), SquareCoordinateArray, gl::STATIC_DRAW);

	// Specify that out coordinate data is going into attribute index 0  and contains three floats per vertex
	gl::VertexAttribPointer(0, 3, gl::FLOAT, gl::FALSE_, 0, 0);

	SquareUV;
	gl::GenBuffers(1, &SquareUV);

	gl::BindBuffer(gl::ARRAY_BUFFER, SquareUV);
	gl::BufferData(gl::ARRAY_BUFFER, sizeof(UV), UV, gl::STATIC_DRAW);
	gl::VertexAttribPointer(1, 2, gl::FLOAT, gl::FALSE_, 0, 0);
}

void Graphics::Drawtext(string text, float x, float y)
{
	Text->RenderText(text, x, y);
}