#version 430 core
layout(location = 0) in vec2 vertexUV;
layout(location = 1) in vec3 vertex;

uniform float XOffset;
uniform float YOffset;
uniform mat4 Camera;

// Interpolated output data
out vec2 UV;
void main()
{
	
	vec4 v = vec4(vertex, 1);

	gl_Position = Camera * v;
	UV = vertexUV;
}
