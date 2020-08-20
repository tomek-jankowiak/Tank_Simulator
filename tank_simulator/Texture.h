#pragma once

#include <GL/glew.h>

class Texture
{
private:
	static GLuint fromPNGfile(const char*, bool generateMipmap = false);

public:
	static void loadTextures();
	static void deleteTextures();

	static GLuint tankMetal, tankSpec, body, track, trackNormal, wheel, rearLight, frontLight, black, 
		grass, grassLightweight, grassPattern;
};

