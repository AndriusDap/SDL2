#include "Includes.h"
#include "Graphics.h"

Graphics::Graphics(int w, int h)
{
	if(!glfwInit())
	{
		cerr << "Error initializing glfw" << endl;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL



	main_window = glfwCreateWindow(w, h, "PEW PEW", NULL, NULL);
	glfwMakeContextCurrent(main_window);
	GLenum glew_error = glewInit();
	if (GLEW_OK != glew_error)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		fprintf(stderr, "Error: %s\n", glewGetErrorString(glew_error));
	}
	cout << "Vendor: " << glGetString(GL_VENDOR) << endl;
	cout << "Renderer: " << glGetString(GL_RENDERER) << endl;
	cout << "OpenGL version: " << glGetString(GL_VERSION) << endl;
	cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;

	if( glew_error != GLEW_OK )
	{
		cerr << "Error initializing GLEW: " << glewGetErrorString(glew_error) << endl;
		exit(1);
	}

	if( !GLEW_VERSION_3_3 )
	{
		cerr << "Error: GL3.3 is required" << endl;
		exit(1);
	}


	glDisable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_MULTISAMPLE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	ProjectionMatrix = glm::ortho((float) 0, (float) w, (float) 0, (float) h, (float) 0.01, (float) 100);

	ViewMatrix = glm::lookAt(
		glm::vec3(0, 0, 3), // Camera location
		glm::vec3(0, 0, 0), // Camera is directed to screen center
		glm::vec3(0, 1, 0)  // Head is up
		);

	Shader.init();
	InitializeRectangle();
	StartRendering();

	glClearColor(0.8f, 0.8f, 0.8f, 1.0);
}

void Graphics::StartRendering()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Shader.begin();
	Shader.setProjection(ProjectionMatrix);
	Shader.setView(ViewMatrix);

	glEnableVertexAttribArray(0);		
	glBindBuffer(GL_ARRAY_BUFFER, SquareVBO);	
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, SquareUV);
	CheckGlErrors();
}

void Graphics::Flip()
{	
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	Shader.end();



	glfwSwapBuffers(main_window);
	glfwPollEvents();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Shader.begin();
	Shader.setProjection(ProjectionMatrix);
	Shader.setView(ViewMatrix);

	glEnableVertexAttribArray(0);		
	glBindBuffer(GL_ARRAY_BUFFER, SquareVBO);	
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, SquareUV);	
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
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		Shader.setTexture(0);
		LastTexture = texture;
	}

	glDrawArrays(GL_TRIANGLES, 0, 6);		
	CheckGlErrors();
}


Graphics::~Graphics(void)
{
	glfwTerminate();
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
	glGenBuffers(1, &SquareVBO);

	// Make it active
	glBindBuffer(GL_ARRAY_BUFFER, SquareVBO);

	// Upload vertex data to gpu
	glBufferData(GL_ARRAY_BUFFER, sizeof(SquareCoordinateArray), SquareCoordinateArray, GL_STATIC_DRAW);

	// Specify that out coordinate data is going into attribute index 0  and contains three floats per vertex
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	SquareUV;
	glGenBuffers(1, &SquareUV);

	glBindBuffer(GL_ARRAY_BUFFER, SquareUV);
	glBufferData(GL_ARRAY_BUFFER, sizeof(UV), UV, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
}
