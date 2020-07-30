#define GLM_FORCE_RADIANS

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cstdio>

#include "Constants.h"
#include "shaderProgram.h"
#include "myCube.h"

void errorCallback(int, const char*);
void keyCallback(GLFWwindow*, int, int, int, int);
void windowResizeCallback(GLFWwindow*, int, int);
GLFWwindow* initWindow();
void initOpenGLProgram(GLFWwindow*);
void freeOpenGLProgram(GLFWwindow*);
void drawScene(GLFWwindow*);

float* vertices = myCubeVertices;
float* normals = myCubeNormals;
float* colors = myCubeColors;
int vertexCount = myCubeVertexCount;

int
currWidth = INITIAL_WIDTH,
currHeight = INITIAL_HEIGHT;

float
speedX = 0,
speedY = 0,
angleX = 0,
angleY = 0;

glm::mat4 P, V, M;

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
            speedX = -PI / 2;
        if (key == GLFW_KEY_RIGHT)
            speedX = PI / 2;
        if (key == GLFW_KEY_UP)
            speedY = PI / 2;
        if (key == GLFW_KEY_DOWN)
            speedY = -PI / 2;
    }

    if (action == GLFW_RELEASE) {
        if (key == GLFW_KEY_LEFT)
            speedX = 0;
        if (key == GLFW_KEY_RIGHT)
            speedX = 0;
        if (key == GLFW_KEY_UP)
            speedY = 0;
        if (key == GLFW_KEY_DOWN)
            speedY = 0;
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

    P = glm::perspective(FOV, (float)INITIAL_WIDTH / INITIAL_HEIGHT, Z_NEAR, Z_FAR);
    V = glm::lookAt(
        glm::vec3(.0f, 0.0f, -5.0f),
        glm::vec3(.0f, .0f, .0f),
        glm::vec3(.0f, 1.0f, .0f)
    );
    M = glm::mat4(1.0f);

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

    angleX = speedX * glfwGetTime();
    angleY = speedY * glfwGetTime();
    glfwSetTime(0);

    M = glm::rotate(M, angleY, glm::vec3(1.0f, .0f, .0f));
    M = glm::rotate(M, angleX, glm::vec3(.0f, 1.0f, .0f));

    glUniformMatrix4fv(ShaderProgram::basicShader->u("P"), 1, false, glm::value_ptr(P));
    glUniformMatrix4fv(ShaderProgram::basicShader->u("V"), 1, false, glm::value_ptr(V));
    glUniformMatrix4fv(ShaderProgram::basicShader->u("M"), 1, false, glm::value_ptr(M));

    glEnableVertexAttribArray(ShaderProgram::basicShader->a("vertex"));
    glVertexAttribPointer(ShaderProgram::basicShader->a("vertex"), 4, GL_FLOAT, false, 0, vertices);

    glEnableVertexAttribArray(ShaderProgram::basicShader->a("color"));
    glVertexAttribPointer(ShaderProgram::basicShader->a("color"), 4, GL_FLOAT, false, 0, colors);

    glDrawArrays(GL_TRIANGLES, 0, vertexCount);

    glfwSwapBuffers(window);
}