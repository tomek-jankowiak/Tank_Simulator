#version 330

uniform sampler2D texMap0;
uniform sampler2D texMap1;

in vec4 n;
in vec4 l;
in vec2 iTexCoord0;
in float layer;

out vec4 pixelColor;


void main(void)
{
	vec4 nnorm = normalize(n);
	vec4 lnorm = normalize(l);

	float df = clamp(dot(nnorm, lnorm), 0, 1);

	vec4 grass = texture(texMap0, iTexCoord0);  // grass pattern
	vec4 grassColor = texture(texMap1, iTexCoord0);  // grass texture
	vec4 color = grassColor;                         
	
	if (layer != 0)	color = vec4(grassColor.rgb, grass.a);
	if (grass.a == 0 && layer != 0)	discard;

	pixelColor = color * vec4(df, df, df, 1);
}