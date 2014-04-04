#include "Includes.h"
#include "Graphics.h"

Graphics::Graphics(int w, int h)
{
	if(!glfwInit())
	{
		cerr << "Error initializing glfw" << endl;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL



	main_window = glfwCreateWindow(w, h, "PEW PEW", NULL, NULL);
	glfwMakeContextCurrent(main_window);

	glewExperimental = true;
	GLenum glew_error = glewInit();
	glGetError();

	if (GLEW_OK != glew_error)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		fprintf(stderr, "Error: %s\n", glewGetErrorString(glew_error));
	}	
	cout << "Vendor: " << glGetString(GL_VENDOR) << endl;
	CheckGlErrors();
	cout << "Renderer: " << glGetString(GL_RENDERER) << endl;
	CheckGlErrors();
	cout << "OpenGL version: " << glGetString(GL_VERSION) << endl;
	CheckGlErrors();
	cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;	
	CheckGlErrors();

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

	CheckGlErrors();
	glDisable(GL_DEPTH_TEST);
	CheckGlErrors();
	glEnable(GL_MULTISAMPLE);
	CheckGlErrors();
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	CheckGlErrors();
	glEnable(GL_BLEND);

	CheckGlErrors();
	ProjectionMatrix = glm::ortho((float) 0, (float) w, (float) 0, (float) h, (float) 0.01, (float) 100);

	ViewMatrix = glm::lookAt(
		glm::vec3(0, 0, 3), // Camera location
		glm::vec3(0, 0, 0), // Camera is directed to screen center
		glm::vec3(0, 1, 0)  // Head is up
		);

	CheckGlErrors();
	Shader.init();
	InitializeRectangle();

	CheckGlErrors();
	StartRendering();

	CheckGlErrors();
	glClearColor(0.8f, 0.8f, 0.8f, 1.0);

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);


	glGenBuffers(1, &ModelTransformationBuffer);
	CheckGlErrors();
	CheckGlErrors();
	FrameQueue.resize(FrameQueueLength);
	FrameCursor = 0;
	LastTexture = 0;
}

void Graphics::StartRendering()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Shader.begin();
	Shader.setProjection(ProjectionMatrix);
	Shader.setView(ViewMatrix);

	glEnableVertexAttribArray(0);		
	CheckGlErrors();
	glBindBuffer(GL_ARRAY_BUFFER, SquareVBO);
	CheckGlErrors();
	glVertexAttribPointer(
		0, //index
		3, //size
		GL_FLOAT, //type
		GL_FALSE, //normalized
		0, //stride
		(void*) 0); // pointer
	CheckGlErrors();
	glEnableVertexAttribArray(1);
	CheckGlErrors();
	glBindBuffer(GL_ARRAY_BUFFER, SquareUV);
	CheckGlErrors();
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*) 0);
	CheckGlErrors();
}
void Graphics::Flip()
{	
	if(FrameCursor != 0)
	{
		FlushBuffer();
	}


	glfwSwapBuffers(main_window);

	CheckGlErrors();
	glfwPollEvents();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

glm::mat4 Graphics::Projection()
{
	return ProjectionMatrix;
}


void Graphics::Render(IRenderable &renderable)
{
	if((LastTexture == renderable.getTexture() || FrameCursor == 0) && FrameCursor < FrameQueueLength)
	{
		LastTexture = renderable.getTexture();
		FrameQueue[FrameCursor] = renderable;
		FrameCursor++;
	}
	else
	{
		FlushBuffer();
		Render(renderable);
	}
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

	glGenBuffers(1, &SquareUV);

	glBindBuffer(GL_ARRAY_BUFFER, SquareUV);
	glBufferData(GL_ARRAY_BUFFER, sizeof(UV), UV, GL_STATIC_DRAW);
}


void Graphics::FlushBuffer()
{
	Shader.setProjection(ProjectionMatrix);
	Shader.setView(ViewMatrix);

	assert(FrameCursor != 0);
	GLuint texture = FrameQueue[0].getTexture();

	// Set texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	Shader.setTexture(0);
	LastTexture = texture;

	vector<float> transformations;
	transformations.reserve(FrameCursor);
	for(size_t i = 0; i < FrameCursor; i++)
	{
		glm::mat4 transformation = FrameQueue[i].getTransformation();
		float *v = &transformation[0][0];
		transformations.insert(transformations.begin() + i * 16, v, v + 16);
	}

	glBindBuffer(GL_ARRAY_BUFFER, ModelTransformationBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * transformations.size(), &transformations[0], GL_DYNAMIC_DRAW);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, (void*) 0);
	glVertexAttribDivisor(2, 4);

	glDrawArrays(GL_TRIANGLES, 0, 6);		
	CheckGlErrors();

	FrameCursor = 0;
}
