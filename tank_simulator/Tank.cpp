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
	tankM = glm::mat4(1.0f);
	moveSpeed = .0f;
	turnSpeed = .0f;
}

void Tank::render()
{
	glUniformMatrix4fv(ShaderProgram::basicShader->u("M"), 1, false, glm::value_ptr(tankM));

	Model::body->render();
	Model::cannon->render();
	Model::turret->render();
}

void Tank::move(float time)
{
	float shift = moveSpeed * time;
	tankM = glm::translate(tankM, glm::vec3(.0f, .0f, shift));
}

void Tank::turn(float time)
{
	float angle = turnSpeed * time;
	tankM = glm::rotate(tankM, angle, glm::vec3(.0f, 1.0f, .0f));
}