#version 330 core
layout(location = 0) in vec3 vertex;
layout(location = 1) in vec2 vertexUV;

layout(location = 2) in vec4 model0;
layout(location = 3) in vec4 model1;
layout(location = 4) in vec4 model2;
layout(location = 5) in vec4 model3;

uniform mat4 View;
uniform mat4 Projection;

// Interpolated output data
out vec2 UV;
void main()
{
	mat4 Model = mat4(model0, model1, model2, model3);
	mat4 MVP = Projection * View * Model;
	vec4 v = vec4(vertex, 1);
	gl_Position = MVP * v;

	UV = vertexUV;
}
