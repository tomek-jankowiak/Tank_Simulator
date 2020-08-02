#version 330

uniform mat4 P;
uniform mat4 V;
uniform mat4 M;

in vec4 vertex;
in vec4 normal;
in vec4 uv;

out vec4 ic;

void main(void)
{
	ic = vec4(1, 1, 1, 1);
	gl_Position = P * V * M * vertex;
}