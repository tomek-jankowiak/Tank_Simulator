#pragma once

#include <GL/glew.h>
#include <vector>

class Texture
{
private:
	static GLuint fromPNGfile(const char*, bool generateMipmap = false);

public:
	static void loadTextures();
	static GLuint loadCubemap(std::vector<const char*>);
	static void deleteTextures();

	static GLuint tankMetal, tankSpec, body, track, trackNormal, trackDepth, wheel, rearLight, frontLight, black, 
		grass, grassLightweight, grassPattern;
};

