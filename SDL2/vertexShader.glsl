#version 430 core
layout(location = 1) in vec3 vertex;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

out vec3 fragmentColor;
void main()
{
	mat4 MVP = Projection * View * Model;
	vec4 v = vec4(vertex, 1);
	gl_Position = MVP * v;

	fragmentColor = vec3(1, 1, 1);
}
