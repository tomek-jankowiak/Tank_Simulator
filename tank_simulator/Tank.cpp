#include "Tank.h"
#include "shaderProgram.h"
#include "constants.h"
#include "Model.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>

Tank::Tank(glm::mat4 &M)
{
	position = glm::vec3(.0f, .0f, .0f);
	bodyM = M;
	turretAngle = .0f;
	cannonAngle = .0f;
	leftSmallWheelsAngle = .0f;
	leftWheelsAngle = .0f;
	rightSmallWheelsAngle = .0f;
	rightWheelsAngle = .0f;

	moveSpeed = .0f;
	turnSpeed = .0f;
	turretTurnSpeed = .0f;
	cannonTurnSpeed = .0f;
}

void Tank::renderTank()
{
	glm::mat4 turretM = glm::translate(bodyM, TANK_TURRET);
	turretM = glm::rotate(turretM, turretAngle, glm::vec3(.0f, 1.0f, .0f));

	glm::mat4 cannonM = glm::translate(turretM, TANK_CANNON);
	cannonM = glm::rotate(cannonM, cannonAngle, glm::vec3(1.0f, .0f, .0f));

	glm::mat4 leftEngineWheelM = glm::translate(bodyM, TANK_LEFT_ENGINE_WHEEL);
	leftEngineWheelM = glm::rotate(leftEngineWheelM, leftWheelsAngle, glm::vec3(1.0f, .0f, .0f));

	glm::mat4 leftSmallWheelM[5];
	for (int i = 0; i < 5; i++) {
		leftSmallWheelM[i] = glm::translate(bodyM, TANK_LEFT_SMALL_WHEELS[i]);
		leftSmallWheelM[i] = glm::rotate(leftSmallWheelM[i], leftSmallWheelsAngle, glm::vec3(1.0f, .0f, .0f));
	}
	
	glm::mat4 leftWheelM[7];
	for (int i = 0; i < 7; i++) {
		leftWheelM[i] = glm::translate(bodyM, TANK_LEFT_WHEELS[i]);
		leftWheelM[i] = glm::rotate(leftWheelM[i], leftWheelsAngle, glm::vec3(1.0f, .0f, .0f));
	}

	glm::mat4 rightEngineWheelM = glm::translate(bodyM, TANK_RIGHT_ENGINE_WHEEL);
	rightEngineWheelM = glm::rotate(rightEngineWheelM, rightWheelsAngle, glm::vec3(1.0f, .0f, .0f));

	glm::mat4 rightSmallWheelM[5];
	for (int i = 0; i < 5; i++) {
		rightSmallWheelM[i] = glm::translate(bodyM, TANK_RIGHT_SMALL_WHEELS[i]);
		rightSmallWheelM[i] = glm::rotate(rightSmallWheelM[i], rightSmallWheelsAngle, glm::vec3(1.0f, .0f, .0f));
	}
	
	glm::mat4 rightWheelM[7];
	for (int i = 0; i < 7; i++) {
		rightWheelM[i] = glm::translate(bodyM, TANK_RIGHT_WHEELS[i]);
		rightWheelM[i] = glm::rotate(rightWheelM[i], rightWheelsAngle, glm::vec3(1.0f, .0f, .0f));
	}
	



	glUniformMatrix4fv(ShaderProgram::basicShader->u("M"), 1, false, glm::value_ptr(bodyM));
	Model::body->render();

	glUniformMatrix4fv(ShaderProgram::basicShader->u("M"), 1, false, glm::value_ptr(turretM));
	Model::turret->render();

	glUniformMatrix4fv(ShaderProgram::basicShader->u("M"), 1, false, glm::value_ptr(cannonM));
	Model::cannon->render();

	glUniformMatrix4fv(ShaderProgram::basicShader->u("M"), 1, false, glm::value_ptr(glm::translate(turretM, TANK_ANTENNA_1)));
	Model::antenna1->render();

	glUniformMatrix4fv(ShaderProgram::basicShader->u("M"), 1, false, glm::value_ptr(glm::translate(turretM, TANK_ANTENNA_2)));
	Model::antenna2->render();

	glUniformMatrix4fv(ShaderProgram::basicShader->u("M"), 1, false, glm::value_ptr(glm::translate(turretM, TANK_HATCH)));
	Model::hatch->render();

	glUniformMatrix4fv(ShaderProgram::basicShader->u("M"), 1, false, glm::value_ptr(leftEngineWheelM));
	Model::leftEngineWheel->render();

	for (int i = 0; i < 5; i++) {
		glUniformMatrix4fv(ShaderProgram::basicShader->u("M"), 1, false, glm::value_ptr(leftSmallWheelM[i]));
		Model::leftSmallWheel->render();
	}

	for (int i = 0; i < 7; i++) {
		glUniformMatrix4fv(ShaderProgram::basicShader->u("M"), 1, false, glm::value_ptr(leftWheelM[i]));
		Model::leftWheel->render();
	}

	glUniformMatrix4fv(ShaderProgram::basicShader->u("M"), 1, false, glm::value_ptr(rightEngineWheelM));
	Model::rightEngineWheel->render();

	for (int i = 0; i < 5; i++) {
		glUniformMatrix4fv(ShaderProgram::basicShader->u("M"), 1, false, glm::value_ptr(rightSmallWheelM[i]));
		Model::rightSmallWheel->render();
	}

	for (int i = 0; i < 7; i++) {
		glUniformMatrix4fv(ShaderProgram::basicShader->u("M"), 1, false, glm::value_ptr(rightWheelM[i]));
		Model::rightWheel->render();
	}

	glUniformMatrix4fv(ShaderProgram::basicShader->u("M"), 1, false, glm::value_ptr(glm::translate(bodyM, TANK_FRONT_LIGHT)));
	Model::frontLight->render();

	glUniformMatrix4fv(ShaderProgram::basicShader->u("M"), 1, false, glm::value_ptr(glm::translate(bodyM, TANK_REAR_LIGHT)));
	Model::rearLight->render();

	glUniformMatrix4fv(ShaderProgram::basicShader->u("M"), 1, false, glm::value_ptr(glm::translate(turretM, TANK_MACHINE_GUN)));
	Model::machineGun->render();

	glUniformMatrix4fv(ShaderProgram::basicShader->u("M"), 1, false, glm::value_ptr(glm::translate(bodyM, TANK_LEFT_TRACK)));
	Model::track->render();

	glUniformMatrix4fv(ShaderProgram::basicShader->u("M"), 1, false, glm::value_ptr(glm::translate(bodyM, TANK_RIGHT_TRACK)));
	Model::track->render();
}

void Tank::moveTank(float time, std::string &mode)
{
	if (mode == "forward") {
		if (moveSpeed >= 0 && moveSpeed < TANK_MAX_FORWARD_SPEED)
			moveSpeed += TANK_ACCELERATION * time;
		else if (moveSpeed < 0)
			moveSpeed += TANK_HAND_BREAK * time;
	}
	else if (mode == "backward") {
		if (moveSpeed <= 0 && moveSpeed > TANK_MAX_BACKWARD_SPEED)
			moveSpeed -= TANK_ACCELERATION * time;
		else if (moveSpeed > 0)
			moveSpeed -= TANK_HAND_BREAK * time;
	}
	else if (mode == "free") {
		if (moveSpeed > 0)
			moveSpeed -= TANK_FREE_BREAK * time;
		else if (moveSpeed < 0)
			moveSpeed += TANK_FREE_BREAK * time;
	}

	leftSmallWheelsAngle += -moveSpeed * time / TANK_SMALL_WHEEL_RADIUS;
	leftWheelsAngle += -moveSpeed * time / TANK_WHEEL_RADIUS;
	rightSmallWheelsAngle += -moveSpeed * time / TANK_SMALL_WHEEL_RADIUS;
	rightWheelsAngle += -moveSpeed * time / TANK_SMALL_WHEEL_RADIUS;

	float shift = moveSpeed * time;
	bodyM = glm::translate(bodyM, glm::vec3(.0f, .0f, -shift));
}

void Tank::turnTank(float time, std::string &direction)
{
	float d = 1.42; // distance between tracks
	float leftTrackSpeed, rightTrackSpeed, r, angle = 0;
	float rotationFactor = PI / 360;

	if (abs(moveSpeed) / TANK_MAX_FORWARD_SPEED > 0.002) {
		if (direction == "left") {
			leftTrackSpeed = 0.6 * moveSpeed;
			rightTrackSpeed = moveSpeed;
			r = (leftTrackSpeed * d) / (rightTrackSpeed - leftTrackSpeed);
			r += d / 2;

			angle = (moveSpeed / r) * (1 - moveSpeed / TANK_MAX_FORWARD_SPEED) * time;
		}
		else if (direction == "right") {
			leftTrackSpeed = moveSpeed;
			rightTrackSpeed = 0.6 * moveSpeed;
			r = (rightTrackSpeed * d) / (leftTrackSpeed - rightTrackSpeed);
			r += d / 2;
			angle = -(moveSpeed / r) * (1 - moveSpeed / TANK_MAX_FORWARD_SPEED) * time;
		}
	}
	else {
		if (direction == "left") {
			angle = rotationFactor;
		}
		else if (direction == "right") {
			angle = -rotationFactor;
		}
		float wheelsAngle = angle * 3;
		leftSmallWheelsAngle += wheelsAngle;
		leftWheelsAngle += wheelsAngle;
		rightSmallWheelsAngle -= wheelsAngle;
		rightWheelsAngle -= wheelsAngle;

	}
	bodyM = glm::rotate(bodyM, angle, glm::vec3(.0f, 1.0f, .0f));
}

void Tank::turnTurret(float time)
{
	turretAngle += turretTurnSpeed * time;
}

void Tank::turnCannon(float time)
{
	if (cannonTurnSpeed > 0 && cannonAngle < TANK_MAX_CANNON_ANGLE)
		cannonAngle += cannonTurnSpeed * time;
	else if (cannonTurnSpeed < 0 && cannonAngle > TANK_MIN_CANNON_ANGLE)
		cannonAngle += cannonTurnSpeed * time;
}