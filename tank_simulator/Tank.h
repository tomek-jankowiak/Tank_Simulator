#pragma once

#include <glm/glm.hpp>

class Tank
{
private:
	glm::vec3 position;
	glm::mat4 bodyM;
	float turretAngle;
	float cannonAngle;

public:
	float moveSpeed;
	float turnSpeed;
	float turretTurnSpeed;
	float cannonTurnSpeed;

	Tank();

	void renderTank();
	glm::mat4 elementM(glm::mat4, glm::vec3);
	void moveTank(float);
	void turnTank(float);
	void turnTurret(float);
	void turnCannon(float);

};

