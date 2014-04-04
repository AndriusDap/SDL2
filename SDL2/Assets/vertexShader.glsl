#version 330 core
layout(location = 0) in vec3 vertex;
layout(location = 1) in vec2 vertexUV;

layout(location = 2) in mat4 Model;

uniform mat4 View;
uniform mat4 Projection;

// Interpolated output data
out vec2 UV;
void main()
{
	mat4 MVP = Projection * View * Model;
	vec4 v = vec4(vertex, 1);
	gl_Position = MVP * v;

	UV = vertexUV;
}
