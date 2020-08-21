#include "Texture.h"

#include "lodepng.h"

#include <vector>

GLuint Texture::tankMetal, Texture::tankSpec, Texture::body, Texture::track, Texture::trackNormal, Texture::trackDepth, Texture::wheel, 
	Texture::rearLight, Texture::frontLight, Texture::black, Texture::grass, Texture::grassLightweight, Texture::grassPattern;

void Texture::loadTextures()
{
	tankMetal = fromPNGfile("textures/tank_metal.png");
	tankSpec = fromPNGfile("textures/tank_spec.png");
	body = fromPNGfile("textures/body.png");
	track = fromPNGfile("textures/track.png");
	trackNormal = fromPNGfile("textures/track_normal.png");
	trackDepth = fromPNGfile("textures/track_depth.png");
	wheel = fromPNGfile("textures/green.png");
	rearLight = fromPNGfile("textures/rearlight.png");
	frontLight = fromPNGfile("textures/frontlight.png");
	black = fromPNGfile("textures/black.png");
	grass = fromPNGfile("textures/grass.png", true);
	grassLightweight = fromPNGfile("textures/grass_lt.png");
	grassPattern = fromPNGfile("textures/grassPattern.png");
	
	printf("Textures loaded.\n");
}

void Texture::deleteTextures()
{
	glDeleteTextures(1, &tankMetal);
	glDeleteTextures(1, &tankSpec);
	glDeleteTextures(1, &body);
	glDeleteTextures(1, &track);
	glDeleteTextures(1, &trackNormal);
	glDeleteTextures(1, &wheel);
	glDeleteTextures(1, &rearLight);
	glDeleteTextures(1, &frontLight);
	glDeleteTextures(1, &black);
	glDeleteTextures(1, &grass);
	glDeleteTextures(1, &grassLightweight);
	glDeleteTextures(1, &grassPattern);
}

GLuint Texture::fromPNGfile(const char *filename, bool generateMipmap)
{
	std::vector<unsigned char> image;
	unsigned width, height;
	unsigned error = lodepng::decode(image, width, height, filename);

	GLuint tex;
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.data());

	if (generateMipmap) {
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	}
	else {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	return tex;
}
