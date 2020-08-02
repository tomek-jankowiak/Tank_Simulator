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

float
speedX = 0,
speedY = 0,
angleX = 0,
angleY = 0;

glm::mat4 P, V, M;

Tank *tank;

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
            tank->turnSpeed = PI / 2;
        if (key == GLFW_KEY_RIGHT)
            tank->turnSpeed = -PI / 2;
        if (key == GLFW_KEY_UP)
            tank->moveSpeed = 3;
        if (key == GLFW_KEY_DOWN)
            tank->moveSpeed = -3;
    }

    if (action == GLFW_RELEASE) {
        if (key == GLFW_KEY_LEFT)
            tank->turnSpeed = 0;
        if (key == GLFW_KEY_RIGHT)
            tank->turnSpeed = 0;
        if (key == GLFW_KEY_UP)
            tank->moveSpeed = 0;
        if (key == GLFW_KEY_DOWN)
            tank->moveSpeed = 0;
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

void initOpenGLProgram(GLFWwindow *window) 
{
    ShaderProgram::loadShaders();
    Model::loadModels();

    P = glm::perspective(FOV, (float)INITIAL_WIDTH / INITIAL_HEIGHT, Z_NEAR, Z_FAR);
    V = glm::lookAt(
        glm::vec3(.0f, 3.0f, -5.0f),
        glm::vec3(.0f, .0f, .0f),
        glm::vec3(.0f, 1.0f, .0f)
    );

    tank = new Tank();

    glClearColor(0, 0, 0, 1);
    glEnable(GL_DEPTH_TEST);

    glfwSetKeyCallback(window, keyCallback);
    glfwSetWindowSizeCallback(window, windowResizeCallback);
}

void freeOpenGLProgram(GLFWwindow* window) 
{
    ShaderProgram::deleteShaders();
}

void drawScene(GLFWwindow* window)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ShaderProgram::basicShader->use();
    glUniformMatrix4fv(ShaderProgram::basicShader->u("P"), 1, false, glm::value_ptr(P));
    glUniformMatrix4fv(ShaderProgram::basicShader->u("V"), 1, false, glm::value_ptr(V));

    if (tank->turnSpeed != 0)
        tank->turn(glfwGetTime());
    if (tank->moveSpeed != 0)
        tank->move(glfwGetTime());
    glfwSetTime(0);
    tank->render();

    glfwSwapBuffers(window);
}