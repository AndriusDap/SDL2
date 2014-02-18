#include "Includes.h"
#include "Graphics.h"
#include "MasterObject.h"
#include "GLHelper.h"
#include "BasicEffect.h"
using namespace std;


int main(int argc, char *argv[])
{

	Graphics g(1600, 900);

	glm::mat4 Projection = g.Projection();
	
	glm::mat4 View = glm::lookAt(
		glm::vec3(4, 3, 3), // Camera location
		glm::vec3(0, 0, 0), // Camera is directed to origin
		glm::vec3(0, 1, 0)  // Head is up
	);

	glm::mat4 Model = glm::mat4(1.0f); // Identity matrix, model is not modified yet

	// Triangle data
	static const GLfloat g_vertex_buffer_data[] = {
	    -1.0f,-1.0f,-1.0f, // triangle 1 : begin
    -1.0f,-1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f, // triangle 1 : end
    1.0f, 1.0f,-1.0f, // triangle 2 : begin
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f, // triangle 2 : end
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f
	};


	GLuint vertexbuffer;
	gl::GenBuffers(1, &vertexbuffer);
	
	gl::BindBuffer(gl::ARRAY_BUFFER, vertexbuffer);
	
	gl::BufferData(gl::ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, gl::STATIC_DRAW);
	CheckGlErrors();


	// User control
	glm::vec3 position = glm::vec3(0, 0, 0);
	// Horizontal angle : to -Z
	float horizontalAngle = (float) PI;
	float verticalAngle = 0.0f;

	float FoV = 45.0f;

	float speed = 3.0f;
	float mouseSpeed = 1.0f;


		// final camera view
	glm::mat4 MVP;

	BasicEffect WrappedShader;

	bool stop = false;
	chrono::time_point<chrono::system_clock> start, end;


	while(!stop){
		
		WrappedShader.begin();
		WrappedShader.setModel(Model);
		WrappedShader.setProjection(Projection);
		WrappedShader.setView(View);

		int VertexBufferLocation = 1;

		gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);
		start = chrono::system_clock::now();
	
		gl::EnableVertexAttribArray(VertexBufferLocation);
		
		gl::BindBuffer(gl::ARRAY_BUFFER, vertexbuffer);
	
		gl::VertexAttribPointer(
			VertexBufferLocation, // Attribute I am now configuring
			3,	// numbers per vertex
			gl::FLOAT, // type
			gl::FALSE_, // Normalized?
			0, // Stride
			0 // Array offset
		); 

		gl::DrawArrays(gl::TRIANGLES, 0, 3*12);
		
		g.Flip();
			
		gl::DisableVertexAttribArray(VertexBufferLocation);
		WrappedShader.end();
		CheckGlErrors();
	
		
		SDL_Delay(1);
		
		end = chrono::system_clock::now();
		chrono::duration<double, milli> duration = end - start;
		float deltaTime = (float) duration.count() * 0.001f;
		int xpos, ypos;
		SDL_GetRelativeMouseState(&xpos, &ypos);
		
		horizontalAngle -= mouseSpeed * deltaTime * float(xpos);
		verticalAngle   -= mouseSpeed * deltaTime * float(ypos);
		glm::vec3 direction(cos(verticalAngle) * sin(horizontalAngle), sin(verticalAngle), cos(verticalAngle) * cos(horizontalAngle));
		glm::vec3 right = glm::vec3(sin(horizontalAngle - PI/2.0f), 0, cos(horizontalAngle - PI/2.0f));
		glm::vec3 up = glm::cross(right, direction);
		
		verticalAngle = fmod(verticalAngle, 2 * (float) PI); 
		horizontalAngle = fmod(horizontalAngle, 2 * (float) PI); 
		

		SDL_PumpEvents();
		
		auto keyboard = SDL_GetKeyboardState(NULL);
		if(keyboard[SDL_SCANCODE_W]){
			position += direction * (float) deltaTime * speed;
		}

		if(keyboard[SDL_SCANCODE_A]){
			position -= right * (float) deltaTime * speed;
		}

		if(keyboard[SDL_SCANCODE_S]){
			position -= direction * (float) deltaTime * speed;
		}

		if(keyboard[SDL_SCANCODE_D]){
			position += right * (float) deltaTime * speed;
		}	
	
		if(keyboard[SDL_SCANCODE_B]){
			cout << "Vertical angle:	" << verticalAngle << "	Horizontal angle:	" << horizontalAngle << endl;
		}

		if(keyboard[SDL_SCANCODE_ESCAPE]){
			stop = true;
		}

		View = glm::lookAt(position, position+direction, up);		
	}
	
	return 0;
}