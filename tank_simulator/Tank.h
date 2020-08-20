#pragma once

#include <glm/glm.hpp>
#include <string>

#include "Model.h"

class Tank
{
private:
	glm::vec3 position;
	glm::mat4 bodyM;
	float bodyAngle;
	float turretAngle;
	float cannonAngle;
	float leftSmallWheelsAngle;
	float leftWheelsAngle;
	float rightSmallWheelsAngle;
	float rightWheelsAngle;

	void renderElement(const Model*, glm::mat4&, GLuint&, GLuint&, GLuint&);
	void updateTankPosition();

public:
	float moveSpeed;
	float turnSpeed;
	float turretTurnSpeed;
	float cannonTurnSpeed;

	Tank(glm::mat4&);

	void renderTank();
	void renderTracks();
	void moveTank(float, std::string&);
	void turnTank(float, std::string&);
	void turnTurret(float);
	void turnCannon(float);

	glm::vec3 getTankPosition();
	float getTankBodyAngle();
};

