#pragma once

#include "constants.h"
#include "Tank.h"

#include <glm/gtc/matrix_transform.hpp>

class Camera
{
private:
	Tank* objToFollow;
	float camDistance;
	float camPitch;  // angle which tells how high/low the camera is
	float camAngle, objAngle;  // angle around the object
	glm::vec3 camPosition, objPosition;
	glm::vec3 camFront, camUp;

public:
	float camVerticalSpeed, camHorizontalSpeed, camZoomSpeed;
	bool camSniperMode;
	
	Camera(Tank* tank);
	void moveCamera(float);

	void calcCamPitch(float);
	void calcCamAngle(float);
	void calcCamZoom(float);
	void lookAtTank();
	
	glm::vec3 getCamPosition();
	glm::mat4 createView();
};
