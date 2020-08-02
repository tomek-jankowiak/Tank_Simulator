#pragma once

#include <glm/glm.hpp>

class Tank
{
private:
	glm::vec3 position;
	glm::mat4 tankM;

public:
	float moveSpeed;
	float turnSpeed;

	Tank();

	void render();
	void move(float);
	void turn(float);

};

