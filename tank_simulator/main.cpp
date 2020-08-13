#define GLM_FORCE_RADIANS

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cstdio>

#include "constants.h"
#include "shaderProgram.h"
#include "Tank.h"
#include "Model.h"
#include "Teren.h"
#include "Camera.h"

void errorCallback(int, const char*);
void keyCallback(GLFWwindow*, int, int, int, int);
void windowResizeCallback(GLFWwindow*, int, int);
GLFWwindow* initWindow();
void initOpenGLProgram(GLFWwindow*);
void freeOpenGLProgram(GLFWwindow*);
void drawScene(GLFWwindow*);

int
currWidth = INITIAL_WIDTH,
currHeight = INITIAL_HEIGHT;

glm::mat4 P, V, M;

std::string
tankMoveMode,
tankTurnDirection;

Tank *tank;
Camera* camera;


int main() 
{
    GLFWwindow* window = initWindow();
    if (window == nullptr)
        return -1;
    
    initOpenGLProgram(window);
    glfwSetTime(0);

    printf("Hello world");

    while (!glfwWindowShouldClose(window)) {
        drawScene(window);
        glfwPollEvents();
    }

    freeOpenGLProgram(window);
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

void errorCallback(int error, const char* description) 
{
    fputs(description, stderr);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_LEFT)
            tankTurnDirection = "left";
        if (key == GLFW_KEY_RIGHT)
            tankTurnDirection = "right";
        if (key == GLFW_KEY_UP)
            tankMoveMode = "forward";
        if (key == GLFW_KEY_DOWN)
            tankMoveMode = "backward";
        if (key == GLFW_KEY_Q)
            tank->turretTurnSpeed = PI / 6;
        if (key == GLFW_KEY_E)
            tank->turretTurnSpeed = -PI / 6;
        if (key == GLFW_KEY_W)
            tank->cannonTurnSpeed = PI / 6;
        if (key == GLFW_KEY_S)
            tank->cannonTurnSpeed = -PI / 6;
        if (key == GLFW_KEY_J)
            camera->camHorizontalSpeed = -PI / 6;
        if (key == GLFW_KEY_L)
            camera->camHorizontalSpeed = PI / 6;
        if (key == GLFW_KEY_K)
            camera->camVerticalSpeed = -PI * 2;
        if (key == GLFW_KEY_I)
            camera->camVerticalSpeed = PI * 2;
    }

    if (action == GLFW_RELEASE) {
        if (key == GLFW_KEY_LEFT)
            tankTurnDirection = "";
        if (key == GLFW_KEY_RIGHT)
            tankTurnDirection = "";
        if (key == GLFW_KEY_UP)
            tankMoveMode = "free";
        if (key == GLFW_KEY_DOWN)
            tankMoveMode = "free";
        if (key == GLFW_KEY_Q)
            tank->turretTurnSpeed = 0;
        if (key == GLFW_KEY_E)
            tank->turretTurnSpeed = 0;
        if (key == GLFW_KEY_W)
            tank->cannonTurnSpeed = 0;
        if (key == GLFW_KEY_S)
            tank->cannonTurnSpeed = 0;
        if (key == GLFW_KEY_J)
            camera->camHorizontalSpeed = .0f;
        if (key == GLFW_KEY_L)
            camera->camHorizontalSpeed = .0f;
        if (key == GLFW_KEY_K)
            camera->camVerticalSpeed = .0f;
        if (key == GLFW_KEY_I)
            camera->camVerticalSpeed = .0f;
    }
}

void windowResizeCallback(GLFWwindow* window, int width, int height) 
{
    currWidth = width;
    currHeight = height;
    if (height == 0) return;
    P = glm::perspective(FOV, (float)width / height, Z_NEAR, Z_FAR);
    glViewport(0, 0, width, height);
}

GLFWwindow* initWindow() 
{
    if (!glfwInit()) {
        fprintf(stderr, "Couldn't initialize GLFW.\n");
        return nullptr;
    }

    glfwSetErrorCallback(errorCallback);

    GLFWwindow *window = glfwCreateWindow(INITIAL_WIDTH, INITIAL_HEIGHT, "Tank Simulator", nullptr, nullptr);

    if (window == nullptr){
        fprintf(stderr, "Couldn't create window.\n");
        glfwTerminate();
        return nullptr;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Couldn't initialize GLEW.\n");
        return nullptr;
    }

    return window;
}

// ------------------------------------------------------------------------------------------

void initOpenGLProgram(GLFWwindow *window) 
{
    ShaderProgram::loadShaders();
    Model::loadModels();

    float terrainTriSize = 2.0f;  // the size of a triangle's side used when building terrain
    Teren::przygotujTeren(terrainTriSize, ZERO_LEVEL, MAX_TERRAIN_N);

    P = glm::perspective(FOV, (float)INITIAL_WIDTH / INITIAL_HEIGHT, Z_NEAR, Z_FAR);
    V = glm::lookAt(
        glm::vec3(.0f, 7.0f, -7.0f),
        glm::vec3(.0f, .0f, .0f),
        glm::vec3(.0f, 1.0f, .0f)
    );
    M = glm::mat4(1.0f);

    tank = new Tank(M);
    camera = new Camera(tank);
    camera->moveCamera(0);

    glClearColor(0, 0, 0, 1);
    glEnable(GL_DEPTH_TEST);

    glfwSetKeyCallback(window, keyCallback);
    glfwSetWindowSizeCallback(window, windowResizeCallback);

}

void freeOpenGLProgram(GLFWwindow* window) 
{
    ShaderProgram::deleteShaders();
    Model::deleteModels();
}

void drawScene(GLFWwindow* window)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    V = glm::lookAt(
            camera->getCamPosition(),
            tank->getTankPosition(),
            glm::vec3(.0f, 1.0f, .0f)
        );

    ShaderProgram::basicShader->use();
    glUniformMatrix4fv(ShaderProgram::basicShader->u("P"), 1, false, glm::value_ptr(P));
    glUniformMatrix4fv(ShaderProgram::basicShader->u("V"), 1, false, glm::value_ptr(V));

    Teren::trawa->renderTeren(
        glm::vec3(MAX_TERRAIN_N * -1.0f, ZERO_LEVEL, MAX_TERRAIN_N * -0.8f)
    );

    tank->turnTank(glfwGetTime(), tankTurnDirection);
    tank->moveTank(glfwGetTime(), tankMoveMode);
    if (tank->turretTurnSpeed != 0)
        tank->turnTurret(glfwGetTime());
    if (tank->cannonTurnSpeed != 0)
        tank->turnCannon(glfwGetTime());
    
    camera->moveCamera(glfwGetTime());

    glfwSetTime(0);
    tank->renderTank();

    glfwSwapBuffers(window);
}