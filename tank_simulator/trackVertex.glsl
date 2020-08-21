#version 330

uniform mat4 P;
uniform mat4 V;
uniform mat4 M;
uniform vec4 light;

layout(location = 0) in vec4 vertex;
layout(location = 1) in vec4 normal;
layout(location = 2) in vec2 uv;
layout(location = 3) in vec4 t;
layout(location = 4) in vec4 b;

out vec2 iTexCoord0;
out vec4 l;
out vec4 v;

void main(void)
{
	mat4 invTBN = transpose(mat4(t, b, normal, vec4(0, 0, 0, 1)));
	
	vec4 tmp = invTBN * vertex;
	l = normalize(invTBN * inverse(M) * light - tmp);
	v = normalize(invTBN * inverse(V * M) * vec4(0, 0, 0, 1) - invTBN * vertex);
	iTexCoord0 = uv;

	gl_Position = P * V * M * vertex;
}