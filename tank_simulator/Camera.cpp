#include "Camera.h"
#include <math.h>

Camera::Camera(Tank* tank)
{
	objToFollow = tank;
	camDistance = 10.0f;
	camPitch = 20.0f;
	camAngle = .0f;
	camVerticalSpeed, camHorizontalSpeed, camZoomSpeed = .0f;
	camSniperMode = false;

	lookAtTank();  
	camFront = glm::vec3(.0f, .0f, -1.0f);
	camUp = glm::vec3(0.0f, 1.0f, 0.0f);
}

void Camera::moveCamera(float time) {

	if (!camSniperMode) {
		calcCamPitch(time);
		calcCamAngle(time);

		lookAtTank();

		float verticalDist = camDistance * sin(radians(camPitch));
		float horizontalDist = camDistance * cos(radians(camPitch));
		float alpha = camAngle + objAngle;

		float offsetX = horizontalDist * sin(alpha);
		float offsetZ = horizontalDist * cos(alpha);

		camPosition.x = objPosition.x + offsetX;
		camPosition.y = objPosition.y + verticalDist;
		camPosition.z = objPosition.z + offsetZ;
	}
	else
	{
		glm::vec3 tmp = objToFollow->getTankPosition();
		camPosition = tmp + TANK_TURRET + TANK_CANNON + glm::vec3(0, 0.5f, -0.1f);
		objPosition = camPosition + camFront;
		/* work in progress
		glm::vec3 direction = glm::vec3(.0f);
		direction.x = cos(glm::radians(objAngle));
		direction.z = sin(glm::radians(objAngle));
		camFront = glm::normalize(direction);

		camPosition += camFront * (time * camZspeed);
		camPosition += glm::normalize(glm::cross(camFront, camUp)) * (time * camXspeed);
		*/
		//printf("c: %f %f %f \nt: %f %f %f\n", camPosition.x, camPosition.y, camPosition.z, objPosition.x, objPosition.y, objPosition.z);
	}
}

void Camera::calcCamPitch(float time) {
	camPitch += camVerticalSpeed * time;
	if (camPitch < CAMERA_MIN_PITCH || camPitch > CAMERA_MAX_PITCH)
		camPitch -= camVerticalSpeed * time;
}
void Camera::calcCamAngle(float time) {
	camAngle += camHorizontalSpeed * time;
}
void Camera::calcCamZoom(float change) {
	camDistance += change;
	if (camDistance < CAMERA_MIN_DIST || camDistance > CAMERA_MAX_DIST)
		camDistance -= change;
}

void Camera::lookAtTank() {
	objPosition = objToFollow->getTankPosition();
	objAngle = objToFollow->getTankBodyAngle();
}

glm::mat4 Camera::createView() {
	return glm::lookAt(camPosition, objPosition, camUp);
}

glm::vec3 Camera::getCamPosition() { return camPosition; }
