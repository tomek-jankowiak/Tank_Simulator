#version 330

uniform sampler2D texMap0;
uniform sampler2D normalMap;
uniform sampler2D depthMap;

in vec2 iTexCoord0;
in vec4 l;
in vec4 v;

out vec4 pixelColor;

vec2 parallaxTexCoords(vec4 view, vec2 texCoords, float heightScale, float s)
{
	vec2 ti = -heightScale * view.xy / s;
	float hi = -1 / s;

	vec2 tc = texCoords;
	float hc = 1;
	float ht = texture(depthMap, tc).r;

	if(view.z <= 0) discard;

	while(hc > ht){
		tc = tc + ti;
		//if(tc.y > 1.0 || tc.y < 0.0) discard;
		hc = hc + hi;
		ht = texture(depthMap, tc).r;
	}

	vec2 tco = tc - ti;
	float hco = hc - hi;
	float hto = texture(depthMap, tco).r;

	float x = (hco - hto) / (hco - hto - (hc - ht));

	return (1 - x) * tco + x * tc;
}

void main(void)
{
	vec4 lightColor = vec4(1, 1, 1, 1);
	float ambientStrength = 0.5;
	float specularStrength = 0.8;

	vec3 ambient = ambientStrength * lightColor.rgb;

	vec4 vnorm = normalize(v);
	vec4 lnorm = normalize(l);

	vec2 texCoords = parallaxTexCoords(vnorm, iTexCoord0, 0.1, 150);
	vec4 nnorm = normalize(vec4(texture(normalMap, texCoords).rgb * 2 - 1, 0 ));
	vec4 objectColor = texture(texMap0, texCoords);

	vec4 rnorm = reflect(-lnorm, nnorm);
	float diff = clamp(dot(nnorm, lnorm), 0, 1);
	vec3 diffuse = diff * lightColor.rgb;

	float spec = pow(clamp(dot(rnorm, vnorm), 0, 1), 32);
	vec3 specular = spec * specularStrength * lightColor.rgb;

	pixelColor = vec4(objectColor.rgb * ambient, objectColor.a) + 
		vec4(objectColor.rgb * diffuse, objectColor.a) + vec4(lightColor.rgb * specular, 0);

}