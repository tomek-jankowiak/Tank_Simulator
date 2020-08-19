#version 330

uniform mat4 P;
uniform mat4 V;
uniform mat4 M;

uniform float maxFurLength;
uniform float maxLayer;

layout(location = 0) in vec4 vertex;
layout(location = 1) in vec4 normal;
layout(location = 2) in vec2 texCoord0;

out vec4 l;
out vec4 n;
out vec2 iTexCoord0;
out float layer;


void main(void) {
	vec4 lightPos = vec4(0, 6, 0, 1);
	l = normalize(V * lightPos - V * M * vertex);
	n = normalize(V * M * normal);
	iTexCoord0 = texCoord0;

	layer = gl_InstanceID;
	vec4 newV = vertex + normalize(normal) * (layer / maxLayer * maxFurLength);

	gl_Position = P * V * M * newV;
}
