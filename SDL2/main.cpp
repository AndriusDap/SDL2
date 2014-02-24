#include "Includes.h"
#include "Graphics.h"
#include "MasterObject.h"
#include "GLHelper.h"
#include "BasicEffect.h"
using namespace std;

int main(int argc, char *argv[])
{

	Graphics g(SCREEN_WIDTH, SCREEN_HEIGHT);

	glm::mat4 Projection = g.Projection();
	
	glm::mat4 View = glm::lookAt(
		glm::vec3(0, 0, 3), // Camera location
		glm::vec3(0, 0, 0), // Camera is directed to screen center
		glm::vec3(0, 1, 0)  // Head is up
	);

	glm::mat4 Model = glm::mat4(1.0f); // Identity matrix, model is not modified yet

	BasicEffect WrappedShader;

	bool stop = false;
	chrono::time_point<chrono::system_clock> start, end;
	
	float SquareCoordinateArray[] = {
		
		 100.5f,  100.5f, 0.0f,
		 -100.5f, -100.5f, 0.0f,};/*
		 100.5f, -100.5f, 0.0f,
		 100.5f,  100.5f, 0.0f,
		 -100.5f, 100.5f, 0.0f,
		 -100.5f,  -100.5f, 0.0f,
	};*/
	float UV[] = {1, 0, 1, 1, 0, 1, 0, 0};


	GLuint SquareVBO;
	// Generate new VBO and store it at SquareVBO
	gl::GenBuffers(1, &SquareVBO);

	// Make it active
	gl::BindBuffer(gl::ARRAY_BUFFER, SquareVBO);

	// Upload vertex data to gpu
	gl::BufferData(gl::ARRAY_BUFFER, sizeof(SquareCoordinateArray), SquareCoordinateArray, gl::STATIC_DRAW);

	// Specify that out coordinate data is going into attribute index 0  and contains three floats per vertex
	gl::VertexAttribPointer(0, 3, gl::FLOAT, gl::FALSE_, 0, 0);




	while(!stop){
		
		WrappedShader.begin();
		WrappedShader.setModel(Model);
		WrappedShader.setProjection(Projection);
		WrappedShader.setView(View);
		gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);
		start = chrono::system_clock::now();
	
		gl::EnableVertexAttribArray(0);
		
		gl::BindBuffer(gl::ARRAY_BUFFER, SquareVBO);
	
		gl::DrawArrays(gl::LINES, 0, 2);
		
		g.Flip();
		WrappedShader.end();
		CheckGlErrors();

		SDL_PumpEvents();
		auto keyboard = SDL_GetKeyboardState(NULL);
		if(keyboard[SDL_SCANCODE_ESCAPE]){
			stop = true;
		}
	}
	
	return 0;
}