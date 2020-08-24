#pragma once
#include "constants.h"
#include "shaderProgram.h"
#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include <vector>
#include <algorithm>

struct Particle {
	glm::vec3 parPosition, parVelocity;
	float parCameraDistance;
	glm::vec4 parColor;
	float parScale;

	Particle()
		: parPosition(0.0f), parVelocity(0.01f), parCameraDistance(10.0f), parColor(1.0f), parScale(0.05f) { }
	
	bool operator<(Particle& that) {
		return this->parCameraDistance > that.parCameraDistance;
	}
};

class ParticleGenerator {
public:
	std::vector<Particle> _allParticles;
	Camera* _camera;
	float _lifeLeft;
	int _parCount;
	std::vector<float> _parVerts, _parColors;

	ParticleGenerator(const std::vector<float>&, Camera*);

	static void prepareParticles(Camera*);
	bool renderParticles(glm::mat4 V, glm::mat4 M);
	void updateParticles();
	void respawnParticles();
	static void deleteParticles();

    static ParticleGenerator* gunpoint;
};