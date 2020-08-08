#pragma once
#include "constants.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include <vector>

class Teren
{
public:
	int terCount;
	std::vector<float> terVerts;

	Teren(const std::vector<float>&);

	static void przygotujTeren(float, float, int);
	void renderTeren(glm::vec3) const;

	static const Teren* trawa;
};