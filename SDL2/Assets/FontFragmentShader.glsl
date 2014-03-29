#version 430 core
out vec4 color;

in vec2 UV;

uniform vec3 Color;
uniform sampler2D TextureSampler;

void main(){
	float alpha = texture(TextureSampler, UV).x;
	color = vec4(Color * alpha, alpha);
}