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
	vec4 color = vec4(1, 1, 1, 1);
	vec4 lightPos = vec4(0, -4, 0, 1);
	vec4 l = normalize(V * lightPos - V * M * vertex);
	vec4 n = normalize(V * M * normal);

	float nl = clamp(dot(n , l), 0, 1);

	ic = vec4(color.rgb * nl, color.a);

	gl_Position = P * V * M * vertex;
}