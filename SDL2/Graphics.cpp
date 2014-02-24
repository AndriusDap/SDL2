#include "Graphics.h"
#include <iostream>

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
	
	SDL_SetRelativeMouseMode(SDL_TRUE);
	main_context = SDL_GL_CreateContext(main_window);
	
	glload::LoadFunctions();
	
	gl::Enable(gl::DEPTH_TEST);
	gl::DepthFunc(gl::LESS);
	gl::Enable(gl::MULTISAMPLE);
	//ProjectionMatrix = glm::ortho((float) 0, (float) w, (float) 0, (float) h, (float) 0.01, (float) 100);
	ProjectionMatrix = glm::ortho((float) -w/2, (float) w/2, (float) -h/2, (float) h/2, (float) 0.01, (float) 100);
}

void Graphics::Flip()
{
	SDL_GL_SwapWindow(main_window);
}

glm::mat4 Graphics::Projection()
{
	return ProjectionMatrix;
}

Graphics::~Graphics(void)
{
	SDL_GL_DeleteContext(main_context);
	SDL_DestroyWindow(main_window);

	SDL_Quit();
}
