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
#include "Texture.h"
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
glm::vec4 light = glm::vec4(.0f, 4.0f, 0.0f, 1.0f);

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
            camera->camHorizontalSpeed = -PI / 3;
        if (key == GLFW_KEY_L)
            camera->camHorizontalSpeed = PI / 3;
        if (key == GLFW_KEY_K)
            camera->camVerticalSpeed = -PI * 6;
        if (key == GLFW_KEY_I)
            camera->camVerticalSpeed = PI * 6;
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
    Texture::loadTextures();

    Teren::prepareTeren(TERRAIN_TRIANGLE_SIZE, ZERO_LEVEL, MAX_TERRAIN_N);

    P = glm::perspective(FOV, (float)INITIAL_WIDTH / INITIAL_HEIGHT, Z_NEAR, Z_FAR);
    M = glm::mat4(1.0f);

    tank = new Tank(M);
    camera = new Camera(tank);
    camera->moveCamera(0);
    V = glm::lookAt(
            camera->getCamPosition(),
            tank->getTankPosition(),
            glm::vec3(.0f, 1.0f, .0f)
        );

    glClearColor(0.4, 0.45, 0.66, 1);
    glEnable(GL_DEPTH_TEST);

    glfwSetKeyCallback(window, keyCallback);
    glfwSetWindowSizeCallback(window, windowResizeCallback);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void freeOpenGLProgram(GLFWwindow* window) 
{
    ShaderProgram::deleteShaders();
    Model::deleteModels();
    Texture::deleteTextures();
    Teren::deleteTeren();
}

void drawScene(GLFWwindow* window)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    V = glm::lookAt(
            camera->getCamPosition(),
            tank->getTankPosition(),
            glm::vec3(.0f, 1.0f, .0f)
        );

    tank->turnTank(glfwGetTime(), tankTurnDirection);
    tank->moveTank(glfwGetTime(), tankMoveMode);
    if (tank->turretTurnSpeed != 0)
        tank->turnTurret(glfwGetTime());
    if (tank->cannonTurnSpeed != 0)
        tank->turnCannon(glfwGetTime());

    camera->moveCamera(glfwGetTime());

    glfwSetTime(0);

    ShaderProgram::terenShader->use();
    glUniformMatrix4fv(ShaderProgram::terenShader->u("P"), 1, false, glm::value_ptr(P));
    glUniformMatrix4fv(ShaderProgram::terenShader->u("V"), 1, false, glm::value_ptr(V));

    float terBorderDistance = MAX_TERRAIN_N * TERRAIN_TRIANGLE_SIZE * -0.5f;
    Teren::grass->renderTeren(
        glm::vec3(terBorderDistance, ZERO_LEVEL, terBorderDistance)
    );

    ShaderProgram::tankShader->use();
    glUniformMatrix4fv(ShaderProgram::tankShader->u("P"), 1, false, glm::value_ptr(P));
    glUniformMatrix4fv(ShaderProgram::tankShader->u("V"), 1, false, glm::value_ptr(V));
    glUniform4fv(ShaderProgram::tankShader->u("light"), 1, glm::value_ptr(light));

    tank->renderTank();

    ShaderProgram::trackShader->use();
    glUniformMatrix4fv(ShaderProgram::trackShader->u("P"), 1, false, glm::value_ptr(P));
    glUniformMatrix4fv(ShaderProgram::trackShader->u("V"), 1, false, glm::value_ptr(V));
    glUniform4fv(ShaderProgram::trackShader->u("light"), 1, glm::value_ptr(light));

    tank->renderTracks();
    
    glfwSwapBuffers(window);
}