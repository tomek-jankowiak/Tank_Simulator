#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <glm/glm.hpp>

const float
PI = 3.141592653589793f,
FOV = 50.0f * PI / 180.0f,
Z_NEAR = 0.01f,
Z_FAR = 150.0f,
TANK_ACCELERATION = 0.5f,
TANK_MAX_FORWARD_SPEED = 20.0f,
TANK_MAX_BACKWARD_SPEED = -5.0f,
TANK_HAND_BREAK = 1.5f,
TANK_FREE_BREAK = 0.7f,
TANK_MAX_CANNON_ANGLE = 20.0f * PI / 180,
TANK_MIN_CANNON_ANGLE = -10.0f * PI / 180,
TANK_SMALL_WHEEL_RADIUS = 0.8f,
TANK_WHEEL_RADIUS = 0.15f,
ZERO_LEVEL = -0.2955f,  // the height value of the lowest point of the tank/track
TERRAIN_TRIANGLE_SIZE = 8.0f,  // the size of a triangle's side used when building terrain
CAMERA_MAX_PITCH = 90.0f,
CAMERA_MIN_PITCH = 5.0f;

const int
INITIAL_WIDTH = 1000,
INITIAL_HEIGHT = 1000,
MAX_TERRAIN_N = 15;  // max number of squares that make up the terrain

using namespace glm;
const vec3
TANK_ANTENNA_1 = vec3(-0.24f, 0.47, -0.36),
TANK_ANTENNA_2 = vec3(0.4f, 0.34f, 0.38f),
TANK_BODY = vec3(0.57f, 0.50f, 0.02f),
TANK_CANNON = vec3(0.0f, 0.02f, -0.8f),
TANK_HATCH = vec3(0.24f, 0.28f, 0.02f),
TANK_LEFT_TRACK = vec3(-0.71f, -0.21f, 0.0f),
TANK_RIGHT_TRACK = vec3(0.71f, -0.21f, 0.0f),
TANK_LEFT_ENGINE_WHEEL = vec3(-0.76f, -0.16f, 1.35f),
TANK_RIGHT_ENGINE_WHEEL = vec3(0.76f, -0.16f, 1.35f),
TANK_FRONT_LIGHT = vec3(-0.53f, 0.21f, -1.42f),
TANK_REAR_LIGHT = vec3(0.0f, 0.12f, 1.50f),
TANK_MACHINE_GUN = vec3(0.0f, 0.34f, 0.27f),
TANK_TURRET = vec3(0.0f, 0.46f, 0.02f),
TANK_LEFT_WHEELS[] = {
	vec3(-0.76f, -0.33f, 1.05f),
	vec3(-0.76f, -0.33f, 0.65f),
	vec3(-0.76f, -0.33f, 0.23f),
	vec3(-0.76f, -0.33f, -0.2f),
	vec3(-0.76f, -0.33f, -0.63f),
	vec3(-0.76f, -0.33f, -1.07f),
	vec3(-0.76f, -0.09f, -1.32f)
},
TANK_RIGHT_WHEELS[] = {
	vec3(0.76f, -0.33f, 1.05f),
	vec3(0.76f, -0.33f, 0.65f),
	vec3(0.76f, -0.33f, 0.23f),
	vec3(0.76f, -0.33f, -0.2f),
	vec3(0.76f, -0.33f, -0.63f),
	vec3(0.76f, -0.33f, -1.07f),
	vec3(0.76f, -0.09f, -1.32f)
},
TANK_LEFT_SMALL_WHEELS[] = {
	vec3(-0.76f, -0.02f, 0.84f),
	vec3(-0.76f, -0.02f, 0.43f),
	vec3(-0.76f, -0.02f, 0.02f),
	vec3(-0.76f, -0.02f, -0.42f),
	vec3(-0.76f, -0.02f, -0.86f)
},
TANK_RIGHT_SMALL_WHEELS[] = {
	vec3(0.76f, -0.02f, 0.84f),
	vec3(0.76f, -0.02f, 0.43f),
	vec3(0.76f, -0.02f, 0.02f),
	vec3(0.76f, -0.02f, -0.42f),
	vec3(0.76f, -0.02f, -0.86f)
};

#endif

