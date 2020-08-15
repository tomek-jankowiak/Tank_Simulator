#version 330

uniform mat4 P;
uniform mat4 V;
uniform mat4 M;
uniform vec4 light;

in vec4 vertex;
in vec4 normal;
in vec2 uv;

out vec2 iTexCoord0;
out vec4 l;
out vec4 n;
out vec4 v;

void main(void)
{
	vec4 tmp = V * M * vertex;
	l = normalize(V * light - tmp);
	n = normalize(V * M * normal);
	v = normalize(-tmp);

	iTexCoord0 = uv;
	gl_Position = P * V * M * vertex;
}