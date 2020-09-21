#version 330

#define LIGHT_COUNT 2

uniform mat4 P;
uniform mat4 V;
uniform mat4 M;
uniform vec4 light[LIGHT_COUNT];

layout(location = 0) in vec4 vertex;
layout(location = 1) in vec4 normal;
layout(location = 2) in vec2 uv;

out vec2 iTexCoord0;
out vec4 l[LIGHT_COUNT];
out vec4 n;
out vec4 v;

void main(void)
{
	vec4 tmp = V * M * vertex;
	n = normalize(V * M * normal);
	v = normalize(-tmp);

	for(int i = 0; i < LIGHT_COUNT; i++){
		l[i] = normalize(V * light[i] - tmp);
	}

	iTexCoord0 = uv;
	gl_Position = P * V * M * vertex;
}