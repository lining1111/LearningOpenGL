#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
#include "Utils.h"

using namespace std;

#define numVAOs 1

GLuint renderingProgram;
GLuint vao[numVAOs];
GLuint locOffsetX;//位置偏移量
float OffsetX = 0.0f;    // location of triangle on offsetX axis
float inc = 0.01f; // offsetX for moving the triangle

const auto basePath = string("chapter2/animation/");

void init(GLFWwindow *window) {
    renderingProgram = Utils::createShaderProgram(string(basePath + "vertShader.glsl").c_str(),
                                                  string(basePath + "fragShader.glsl").c_str());
    glGenVertexArrays(numVAOs, vao);//获取顶点数组对象
    glBindVertexArray(vao[0]);//绑定顶点数组对象
}

void display(GLFWwindow *window, double currentTime) {
    glClear(GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);  // clear the background to black, each time

    glUseProgram(renderingProgram);
    //locOffsetX是顶点着色器中的地址位置，x为传递的值。
    OffsetX += inc;   // move the triangle along offsetX axis
    if (OffsetX > 1.0f) {
        inc = -0.01f;  // switch to moving the triangle to the left
    } else if (OffsetX < -1.0f) {
        inc = 0.01f;  // switch to moving the triangle to the right
    }
    locOffsetX = glGetUniformLocation(renderingProgram, "OffsetX"); // get ptr to "offsetX" 对应 vertShader.glsl 第3行声明的变量
    glProgramUniform1f(renderingProgram, locOffsetX, OffsetX);  // send value in "offsetX" to "offsetX"
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

int main(void) {
    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    GLFWwindow *window = glfwCreateWindow(400, 200, "Chapter 2 - program 6", NULL, NULL);
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK) {
        exit(EXIT_FAILURE);
    }
    glfwSwapInterval(1);

    init(window);

    while (!glfwWindowShouldClose(window)) {
        display(window, glfwGetTime());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}