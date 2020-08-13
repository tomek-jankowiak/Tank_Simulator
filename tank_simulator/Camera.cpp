#include "Camera.h"
#include <math.h>

Camera::Camera(Tank* tank)
{
	objToFollow = tank;
	camDistance = 10.0f;
	camPitch = 20.0f;
	camAngle = .0f;
	camVerticalSpeed = .0f;
	camHorizontalSpeed = .0f;
	updateCamPosition();
}

void Camera::moveCamera(float time) {
	updateCamPosition();
	calcCamPitch(time);
	calcCamAngle(time);

	float verticalDist = camDistance * sin(radians(camPitch));
	float horizontalDist = camDistance * cos(radians(camPitch));
	float alpha = objToFollow->getTankBodyAngle() + camAngle;

	float offsetX = horizontalDist * sin(alpha);
	float offsetZ = horizontalDist * cos(alpha);

	camPosition.x += offsetX;
	camPosition.y += verticalDist;
	camPosition.z += offsetZ;
}

void Camera::calcCamPitch(float time) {
	camPitch += camVerticalSpeed * time;
}
void Camera::calcCamAngle(float time) {
	camAngle += camHorizontalSpeed * time;
}
void Camera::updateCamPosition() {
	camPosition = objToFollow->getTankPosition();
}

glm::vec3 Camera::getCamPosition() { return camPosition; }
