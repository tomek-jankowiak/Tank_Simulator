#version 330

#define LIGHT_COUNT 2

uniform sampler2D texMap0;
uniform sampler2D texMap1;
uniform sampler2D texMap2;

in vec2 iTexCoord0;
in vec4 l[LIGHT_COUNT];
in vec4 n;
in vec4 v;

out vec4 pixelColor;

void main(void)
{
	vec4 lightColor = vec4(1, 1, 1, 1);
	float ambientStrength = 0.2;
	float specularStrength = 0.5;

	vec3 ambient = ambientStrength * lightColor.rgb;

	vec4 nnorm = normalize(n);
	vec4 vnorm = normalize(v);
		
	vec4 objectColor = mix(texture(texMap0, iTexCoord0), texture(texMap1, iTexCoord0), 0.3);
	vec4 specColor = texture(texMap2, iTexCoord0);

	pixelColor = vec4(objectColor.rgb * ambient, objectColor.a);

	for(int i = 0; i < LIGHT_COUNT; i++){
		vec4 lnorm = normalize(l[i]);
		vec4 rnorm = reflect(-lnorm, nnorm);

		float diff = clamp(dot(nnorm, lnorm), 0, 1);
		vec3 diffuse = diff * lightColor.rgb;

		float spec = pow(clamp(dot(rnorm, vnorm), 0, 1), 64);
		vec3 specular = spec * specularStrength * lightColor.rgb;

		pixelColor += vec4(objectColor.rgb * diffuse, objectColor.a) + vec4(specColor.rgb * specular, 0);
	}

}