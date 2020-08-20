#pragma once

#include <GL/glew.h>

class Texture
{
private:
	static GLuint fromPNGfile(const char*);

public:
	static void loadTextures();
	static void deleteTextures();

	static GLuint tankMetal, tankSpec, body, track, wheel, rearLight, frontLight, black;
	static GLuint grass, grassLightweight, grassPattern;
};

