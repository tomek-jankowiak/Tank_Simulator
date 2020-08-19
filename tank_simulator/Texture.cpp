#include "Texture.h"

#include "lodepng.h"

#include <vector>

GLuint Texture::body, Texture::track, Texture::wheel, Texture::rearLight, Texture::frontLight, Texture::black;
GLuint Texture::grass, Texture::grassLightweight, Texture::grassPattern;

void Texture::loadTextures()
{
	body = fromPNGfile("textures/body.png");
	track = fromPNGfile("textures/track.png");
	wheel = fromPNGfile("textures/green.png");
	rearLight = fromPNGfile("textures/rearlight.png");
	frontLight = fromPNGfile("textures/frontlight.png");
	black = fromPNGfile("textures/black.png");
	grass = fromPNGfile("textures/grass.png");
	grassLightweight = fromPNGfile("textures/grass_lt.png");
	grassPattern = fromPNGfile("textures/grassPattern.png");
	printf("Textures loaded.\n");
}

void Texture::deleteTextures()
{
	glDeleteTextures(1, &body);
	glDeleteTextures(1, &track);
	glDeleteTextures(1, &wheel);
	glDeleteTextures(1, &rearLight);
	glDeleteTextures(1, &frontLight);
	glDeleteTextures(1, &black);
	glDeleteTextures(1, &grass);
	glDeleteTextures(1, &grassLightweight);
	glDeleteTextures(1, &grassPattern);
}

GLuint Texture::fromPNGfile(const char *filename)
{
	std::vector<unsigned char> image;
	unsigned width, height;
	unsigned error = lodepng::decode(image, width, height, filename);

	GLuint tex;
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.data());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	return tex;
}
