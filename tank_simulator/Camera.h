#pragma once

#include "constants.h"
#include "Tank.h"


class Camera
{
private:
	float camDistance;
	float camPitch;  // angle which tells how high/low the camera is
	float camAngle;  // angle around the object
	Tank* objToFollow;
	glm::vec3 camPosition;

public:
	float camVerticalSpeed, camHorizontalSpeed;
	
	Camera(Tank* tank);
	void moveCamera(float);

	void calcCamPitch(float);
	void calcCamAngle(float);
	void updateCamPosition();
	
	glm::vec3 getCamPosition();
};
