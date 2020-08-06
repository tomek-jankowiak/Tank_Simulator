#include "Tank.h"
#include "shaderProgram.h"
#include "constants.h"
#include "Model.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>

Tank::Tank()
{
	position = glm::vec3(.0f, .0f, .0f);
	bodyM = glm::mat4(1.0f);
	turretAngle = .0f;
	cannonAngle = .0f;

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

	glm::mat4 leftSmallWheelM[5];
	for (int i = 0; i < 5; i++)
		leftSmallWheelM[i] = glm::translate(bodyM, TANK_LEFT_SMALL_WHEELS[i]);
	
	glm::mat4 leftWheelM[7];
	for (int i = 0; i < 7; i++)
		leftWheelM[i] = glm::translate(bodyM, TANK_LEFT_WHEELS[i]);

	glm::mat4 rightEngineWheelM = glm::translate(bodyM, TANK_RIGHT_ENGINE_WHEEL);
	
	glm::mat4 rightSmallWheelM[5];
	for (int i = 0; i < 5; i++)
		rightSmallWheelM[i] = glm::translate(bodyM, TANK_RIGHT_SMALL_WHEELS[i]);
	
	glm::mat4 rightWheelM[7];
	for (int i = 0; i < 7; i++)
		rightWheelM[i] = glm::translate(bodyM, TANK_RIGHT_WHEELS[i]);
	



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

glm::mat4 Tank::elementM(glm::mat4 basicM, glm::vec3 postion)
{
	glm::mat4 M = basicM;
	M = glm::translate(M, position);
	return M;
}

void Tank::moveTank(float time)
{
	float shift = moveSpeed * time;
	bodyM = glm::translate(bodyM, glm::vec3(.0f, .0f, shift));
}

void Tank::turnTank(float time)
{
	float angle = turnSpeed * time;
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