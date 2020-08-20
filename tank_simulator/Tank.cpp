#include "Tank.h"
#include "shaderProgram.h"
#include "constants.h"
#include "Texture.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Tank::Tank(glm::mat4 &M)
{
	position = glm::vec3(.0f, .0f, .0f);
	bodyM = M;
	bodyAngle = .0f;
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

void Tank::renderElement(const Model* element, glm::mat4& M, GLuint &texture0, GLuint &texture1, GLuint &spec)
{
	glUniformMatrix4fv(ShaderProgram::tankShader->u("M"), 1, false, glm::value_ptr(M));
	glUniform1i(ShaderProgram::tankShader->u("texMap0"), 0);
	glUniform1i(ShaderProgram::tankShader->u("texMap1"), 1);
	glUniform1i(ShaderProgram::tankShader->u("texMap2"), 2);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, spec);
	element->render();
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
	
	renderElement(Model::body, bodyM, Texture::body, Texture::tankMetal, Texture::tankSpec);
	renderElement(Model::turret, turretM, Texture::body, Texture::tankMetal, Texture::tankSpec);
	renderElement(Model::cannon, cannonM, Texture::body, Texture::tankMetal, Texture::tankSpec);
	renderElement(Model::leftEngineWheel, leftEngineWheelM, Texture::wheel, Texture::tankMetal, Texture::tankSpec);
	renderElement(Model::rightEngineWheel, rightEngineWheelM, Texture::wheel, Texture::tankMetal, Texture::tankSpec);

	for (int i = 0; i < 5; i++) {
		renderElement(Model::leftSmallWheel, leftSmallWheelM[i], Texture::wheel, Texture::tankMetal, Texture::tankSpec);
	}

	for (int i = 0; i < 7; i++) {
		renderElement(Model::leftWheel, leftWheelM[i], Texture::wheel, Texture::tankMetal, Texture::tankSpec);
	}

	for (int i = 0; i < 5; i++) {
		renderElement(Model::rightSmallWheel, rightSmallWheelM[i], Texture::wheel, Texture::tankMetal, Texture::tankSpec);
	}

	for (int i = 0; i < 7; i++) {
		renderElement(Model::rightWheel, rightWheelM[i], Texture::wheel, Texture::tankMetal, Texture::tankSpec);
	}

	glm::mat4 tmpM;
	tmpM = glm::translate(turretM, TANK_ANTENNA_1);
	renderElement(Model::antenna1, tmpM, Texture::black, Texture::tankMetal, Texture::tankSpec);

	tmpM = glm::translate(turretM, TANK_ANTENNA_2);
	renderElement(Model::antenna2, tmpM, Texture::black, Texture::tankMetal, Texture::tankSpec);

	tmpM = glm::translate(turretM, TANK_HATCH);
	renderElement(Model::hatch, tmpM, Texture::body, Texture::tankMetal, Texture::tankSpec);

	tmpM = glm::translate(bodyM, TANK_FRONT_LIGHT);
	renderElement(Model::frontLight, tmpM, Texture::frontLight, Texture::tankMetal, Texture::tankSpec);

	tmpM = glm::translate(bodyM, TANK_REAR_LIGHT);
	renderElement(Model::rearLight, tmpM, Texture::rearLight, Texture::tankMetal, Texture::tankSpec);

	tmpM = glm::translate(turretM, TANK_MACHINE_GUN);
	renderElement(Model::machineGun, tmpM, Texture::black, Texture::tankMetal, Texture::tankSpec);

}

void Tank::renderTracks()
{
	glUniformMatrix4fv(ShaderProgram::trackShader->u("M"), 1, false, glm::value_ptr(glm::translate(bodyM, TANK_LEFT_TRACK)));
	glUniform1i(ShaderProgram::trackShader->u("texMap0"), 0);
	glUniform1i(ShaderProgram::trackShader->u("normalMap"), 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Texture::track);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, Texture::trackNormal);
	Model::track->renderNormalMapping();

	glUniformMatrix4fv(ShaderProgram::trackShader->u("M"), 1, false, glm::value_ptr(glm::translate(bodyM, TANK_RIGHT_TRACK)));
	glUniform1i(ShaderProgram::trackShader->u("texMap0"), 0);
	glUniform1i(ShaderProgram::trackShader->u("normalMap"), 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Texture::track);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, Texture::trackNormal);
	Model::track->renderNormalMapping();
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
	rightWheelsAngle += -moveSpeed * time / TANK_WHEEL_RADIUS;

	float shift = moveSpeed * time;
	bodyM = glm::translate(bodyM, glm::vec3(.0f, .0f, -shift));
	updateTankPosition();
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
	bodyAngle += angle;
	updateTankPosition();
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

void Tank::updateTankPosition() {
	position = glm::vec3(bodyM[3].x, bodyM[3].y, bodyM[3].z);
}

glm::vec3 Tank::getTankPosition() { return position; }
float Tank::getTankBodyAngle() { return bodyAngle; }
