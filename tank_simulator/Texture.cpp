#include "Texture.h"

#include "lodepng.h"

#include <vector>

GLuint Texture::body, Texture::track, Texture::wheel, Texture::black, Texture::grass;

void Texture::loadTextures()
{
	body = fromPNGfile("textures/body.png");
	track = fromPNGfile("textures/track.png");
	black = fromPNGfile("textures/black.png");
	grass = fromPNGfile("textures/grass.png");
	printf("Textures loaded.\n");
}

void Texture::deleteTextures()
{
	glDeleteTextures(1, &body);
	glDeleteTextures(1, &track);
	glDeleteTextures(1, &wheel);
	glDeleteTextures(1, &black);
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
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	return tex;
}
