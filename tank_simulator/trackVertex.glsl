#version 330

#define LIGHT_COUNT 2

uniform mat4 P;
uniform mat4 V;
uniform mat4 M;
uniform vec4 light[LIGHT_COUNT];

layout(location = 0) in vec4 vertex;
layout(location = 1) in vec4 normal;
layout(location = 2) in vec2 uv;
layout(location = 3) in vec4 t;
layout(location = 4) in vec4 b;

out vec2 iTexCoord0;
out vec4 l[LIGHT_COUNT];
out vec4 v;

void main(void)
{
	mat4 invTBN = transpose(mat4(t, b, normal, vec4(0, 0, 0, 1)));
	
	vec4 tmp = invTBN * vertex;
	for(int i = 0; i < LIGHT_COUNT; i++){
		l[i] = normalize(invTBN * inverse(M) * light[i] - tmp);
	}
	v = normalize(invTBN * inverse(V * M) * vec4(0, 0, 0, 1) - invTBN * vertex);
	iTexCoord0 = uv;

	gl_Position = P * V * M * vertex;
}