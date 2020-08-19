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
	int _terCount;
	std::vector<float> _terVerts, _terNorms, _terUV;

	Teren(const std::vector<float>&, const std::vector<float>&, const std::vector<float>&);

	static void prepareTeren(float, float, int);
	void renderTeren(glm::vec3) const;
	static void deleteTeren();

	static const Teren* grass;
};