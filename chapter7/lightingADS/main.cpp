#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include <fstream>
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include "Torus.h"
#include "Utils.h"

using namespace std;

float toRadians(float degrees) {
    return (degrees * 2.0f * 3.14159f) / 360.0f;
}

#define numVAOs 1
#define numVBOs 4

float cameraX, cameraY, cameraZ;
float torLocX, torLocY, torLocZ;
GLuint renderingProgram;
GLuint vao[numVAOs];
GLuint vbo[numVBOs];

Torus myTorus(0.5f, 0.2f, 48);
int numTorusVertices = myTorus.getNumVertices();
int numTorusIndices = myTorus.getNumIndices();

// 初始化光照位置
glm::vec3 initialLightLoc = glm::vec3(5.0f, 2.0f, 2.0f);
float amt = 0.0f;

// variable allocation for display
GLuint mvLoc, projLoc, nLoc;
// 着色器统一变量中的位置
GLuint globalAmbLoc, ambLoc, diffLoc, specLoc, posLoc, mambLoc, mdiffLoc, mspecLoc, mshiLoc;
int width, height;
float aspect;
glm::mat4 pMat, vMat, mMat, mvMat, invTrMat, rMat;
glm::vec3 currentLightPos, transformed;
float lightPos[3];

// 白光特性
float globalAmbient[4] = {0.7f, 0.7f, 0.7f, 1.0f};//全局光
float lightAmbient[4] = {0.0f, 0.0f, 0.0f, 1.0f};//环境光反射
float lightDiffuse[4] = {1.0f, 1.0f, 1.0f, 1.0f};//漫反射
float lightSpecular[4] = {1.0f, 1.0f, 1.0f, 1.0f};//镜面反射

// 黄金材质特性
float *matAmb = Utils::goldAmbient();
float *matDif = Utils::goldDiffuse();
float *matSpe = Utils::goldSpecular();
float matShi = Utils::goldShininess();

void installLights(glm::mat4 vMatrix) {
    //将光源位置转换为视图空间坐标，并存入浮点数组
    transformed = glm::vec3(vMatrix * glm::vec4(currentLightPos, 1.0));
    lightPos[0] = transformed.x;
    lightPos[1] = transformed.y;
    lightPos[2] = transformed.z;

    // 在着色器中获取光源位置和材质属性
    globalAmbLoc = glGetUniformLocation(renderingProgram, "globalAmbient");
    ambLoc = glGetUniformLocation(renderingProgram, "light.ambient");
    diffLoc = glGetUniformLocation(renderingProgram, "light.diffuse");
    specLoc = glGetUniformLocation(renderingProgram, "light.specular");
    posLoc = glGetUniformLocation(renderingProgram, "light.position");
    mambLoc = glGetUniformLocation(renderingProgram, "material.ambient");
    mdiffLoc = glGetUniformLocation(renderingProgram, "material.diffuse");
    mspecLoc = glGetUniformLocation(renderingProgram, "material.specular");
    mshiLoc = glGetUniformLocation(renderingProgram, "material.shininess");

    //  在着色器中为光源与材质统一变量赋值
    glProgramUniform4fv(renderingProgram, globalAmbLoc, 1, globalAmbient);
    glProgramUniform4fv(renderingProgram, ambLoc, 1, lightAmbient);
    glProgramUniform4fv(renderingProgram, diffLoc, 1, lightDiffuse);
    glProgramUniform4fv(renderingProgram, specLoc, 1, lightSpecular);
    glProgramUniform3fv(renderingProgram, posLoc, 1, lightPos);
    glProgramUniform4fv(renderingProgram, mambLoc, 1, matAmb);
    glProgramUniform4fv(renderingProgram, mdiffLoc, 1, matDif);
    glProgramUniform4fv(renderingProgram, mspecLoc, 1, matSpe);
    glProgramUniform1f(renderingProgram, mshiLoc, matShi);
}

void setupVertices(void) {
    std::vector<int> ind = myTorus.getIndices();
    std::vector<glm::vec3> vert = myTorus.getVertices();
    std::vector<glm::vec2> tex = myTorus.getTexCoords();
    std::vector<glm::vec3> norm = myTorus.getNormals();

    std::vector<float> pvalues;
    std::vector<float> tvalues;
    std::vector<float> nvalues;

    for (int i = 0; i < myTorus.getNumVertices(); i++) {
        pvalues.push_back(vert[i].x);
        pvalues.push_back(vert[i].y);
        pvalues.push_back(vert[i].z);
        tvalues.push_back(tex[i].s);
        tvalues.push_back(tex[i].t);
        nvalues.push_back(norm[i].x);
        nvalues.push_back(norm[i].y);
        nvalues.push_back(norm[i].z);
    }
    glGenVertexArrays(1, vao);
    glBindVertexArray(vao[0]);
    glGenBuffers(numVBOs, vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, pvalues.size() * 4, &pvalues[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, tvalues.size() * 4, &tvalues[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
    glBufferData(GL_ARRAY_BUFFER, nvalues.size() * 4, &nvalues[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[3]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, ind.size() * 4, &ind[0], GL_STATIC_DRAW);
}

const auto basePath = string("chapter7/lightingADS/");

void init(GLFWwindow *window) {
    auto sub = string("GouraudShaders/");
//    auto sub = string("PhongShaders/");
//    auto sub = string("BlinnPhongShaders/");
    renderingProgram = Utils::createShaderProgram(string(basePath + sub + "vertShader.glsl").c_str(),
                                                  string(basePath + sub + "fragShader.glsl").c_str());
    cameraX = 0.0f;
    cameraY = 0.0f;
    cameraZ = 1.0f;
    torLocX = 0.0f;
    torLocY = 0.0f;
    torLocZ = -1.0f;

    glfwGetFramebufferSize(window, &width, &height);
    aspect = (float) width / (float) height;
    pMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f);

    setupVertices();
}

void display(GLFWwindow *window, double currentTime) {
    glClear(GL_DEPTH_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(renderingProgram);

    mvLoc = glGetUniformLocation(renderingProgram, "mv_matrix");
    projLoc = glGetUniformLocation(renderingProgram, "proj_matrix");
    nLoc = glGetUniformLocation(renderingProgram, "norm_matrix");

    vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ));
    //基于环面位置，构建模型矩阵
    mMat = glm::translate(glm::mat4(1.0f), glm::vec3(torLocX, torLocY, torLocZ));
    //旋转环面以便更容易看到
    mMat *= glm::rotate(mMat, toRadians(35.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    //基于当前光源位置，初始化光照
    currentLightPos = glm::vec3(initialLightLoc.x, initialLightLoc.y, initialLightLoc.z);
    amt = currentTime * 25.0f;
    rMat = glm::rotate(glm::mat4(1.0f), toRadians(amt), glm::vec3(0.0f, 0.0f, 1.0f));
    currentLightPos = glm::vec3(rMat * glm::vec4(currentLightPos, 1.0f));

    //光照模式下，修改视图矩阵
    installLights(vMat);
    //通过合并模型和视图矩阵来计算MV矩阵
    mvMat = vMat * mMat;
    //构建MV矩阵的逆转置矩阵，以变换法向量
    invTrMat = glm::transpose(glm::inverse(mvMat));
    //将MV、PROJ以及逆转置矩阵统一传入相应的统一变量
    glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));
    glUniformMatrix4fv(nLoc, 1, GL_FALSE, glm::value_ptr(invTrMat));

    //在顶点着色器中，将顶点缓冲区绑定到顶点属性0
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);
    //在顶点着色器中，将法向量缓冲区绑定到顶点属性1
    glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[3]);
    glDrawElements(GL_TRIANGLES, numTorusIndices, GL_UNSIGNED_INT, 0);
}

void window_size_callback(GLFWwindow *win, int newWidth, int newHeight) {
    aspect = (float) newWidth / (float) newHeight;
    glViewport(0, 0, newWidth, newHeight);
    pMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f);
}

int main(void) {
    if (!glfwInit()) { exit(EXIT_FAILURE); }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    GLFWwindow *window = glfwCreateWindow(800, 800, "Chapter 7 - program 1", NULL, NULL);
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK) { exit(EXIT_FAILURE); }
    glfwSwapInterval(1);

    glfwSetWindowSizeCallback(window, window_size_callback);

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