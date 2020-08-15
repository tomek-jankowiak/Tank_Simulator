#version 330

uniform sampler2D texMap0;

in vec2 iTexCoord0;
in vec4 l;
in vec4 n;
in vec4 v;

out vec4 pixelColor;

void main(void)
{
	vec4 lnorm = normalize(l);
	vec4 nnorm = normalize(n);
	vec4 vnorm = normalize(v);
	vec4 rnorm = reflect(-lnorm, nnorm);

	vec4 kd = texture(texMap0, iTexCoord0);
	vec4 ks = vec4(1, 1, 1, 1);

	float nl = clamp(dot(nnorm, lnorm), 0, 1);
	float rv = pow(clamp(dot(rnorm, vnorm), 0, 1), 50);

	pixelColor = vec4(kd.rgb * nl, kd.a) + vec4(ks.rgb * rv, 0);
}