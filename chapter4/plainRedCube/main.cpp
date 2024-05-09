#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include "Utils.h"

using namespace std;

#define numVAOs 1
#define numVBOs 2

Utils util = Utils();
glm::vec3 camera;//相机位置
glm::vec3 cube;//立方体位置
GLuint renderingProgram;
GLuint vao[numVAOs];//顶点数组对象
GLuint vbo[numVBOs];//顶点缓冲对象

// 分配在display()函数中使用的局部变量，这样就不需要在display()函数中重复声明它们
GLuint mvLoc, projLoc;
int width, height;//窗口宽度和高度
float fov;//视野
float aspect;//窗口宽高比
glm::mat4 pMat, vMat, mMat, mvMat;//投影矩阵，视图矩阵，模型矩阵，模型视图矩阵

//36个顶点 12个三角形 组成放置在原点的立方体，一个立方体6个面，每个面2个三角形、每个三角形3个顶点
//下面的数组应该这样看，每3个为一组，每两组组成一个面,8个顶点，
//造成顶点因位置不同而重复次数不同的原因是：三角形的顶点按特定顺序来，重复的是都是起始节点，不重复的是中间节点
//(1,1,1) *5 //前右上
//(-1,1,1) *4 //前左上
//(-1,-1,1) *5 //前左下
//(1,-1,1) *4 //前右下
//(1,1,-1) *4 //后右上
//(-1,1,-1) *5 //后左上
//(-1,-1,-1) *4 //后左下
//(1,-1,-1) *4 //后右下
void setupVertices(void) {
    float vertexPositions[108] = {
            -1.0f, 1.0f, -1.0f,//(-1,1,-1)
            -1.0f, -1.0f, -1.0f,//(-1,-1,-1)
            1.0f, -1.0f, -1.0f,//(1,-1,-1)
            1.0f, -1.0f, -1.0f,//(1,-1,-1)
            1.0f, 1.0f, -1.0f,//(1,1,-1)
            -1.0f, 1.0f, -1.0f,//(-1,1,-1)
            1.0f, -1.0f, -1.0f,//(1,-1,-1)
            1.0f, -1.0f, 1.0f,//(1,-1,1)
            1.0f, 1.0f, -1.0f,//(1,1,-1)
            1.0f, -1.0f, 1.0f,//(1,-1,1)
            1.0f, 1.0f, 1.0f,//(1,1,1)
            1.0f, 1.0f, -1.0f,//(1,1,-1)
            1.0f, -1.0f, 1.0f,//(1,-1,1)
            -1.0f, -1.0f, 1.0f,//(-1,-1,1)
            1.0f, 1.0f, 1.0f,//(1,1,1)
            -1.0f, -1.0f, 1.0f,//(-1,-1,1)
            -1.0f, 1.0f, 1.0f,//(-1,1,1)
            1.0f, 1.0f, 1.0f,//(1,1,1)
            -1.0f, -1.0f, 1.0f,//(-1,-1,1)
            -1.0f, -1.0f, -1.0f,//(-1,-1,-1)
            -1.0f, 1.0f, 1.0f,//(-1,1,1)
            -1.0f, -1.0f, -1.0f,//(-1,-1,-1)
            -1.0f, 1.0f, -1.0f,//(-1,1,-1)
            -1.0f, 1.0f, 1.0f,//(-1,1,1)
            -1.0f, -1.0f, 1.0f,//(-1,-1,1)
            1.0f, -1.0f, 1.0f,//(1,-1,1)
            1.0f, -1.0f, -1.0f,//(1,-1,-1)
            1.0f, -1.0f, -1.0f,//(1,-1,-1)
            -1.0f, -1.0f, -1.0f,//(-1,-1,-1)
            -1.0f, -1.0f, 1.0f,//(-1,-1,1)
            -1.0f, 1.0f, -1.0f,//(-1,1,-1)
            1.0f, 1.0f, -1.0f,//(1,1,-1)
            1.0f, 1.0f, 1.0f,//(1,1,1)
            1.0f, 1.0f, 1.0f,//(1,1,1)
            -1.0f, 1.0f, 1.0f,//(-1,1,1)
            -1.0f, 1.0f, -1.0f//(-1,1,-1)
    };

    //创建顶点数组对象VAO
    glGenVertexArrays(numVAOs, vao);
    glBindVertexArray(vao[0]);
    //创建顶点缓冲对象VBO
    glGenBuffers(numVBOs, vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    //将顶点数据复制到缓冲中供OpenGL使用
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);
}

const auto basePath = string("chapter4/plainRedCube/");

void init(GLFWwindow *window) {
    renderingProgram = Utils::createShaderProgram(string(basePath + "vertShader.glsl").c_str(),
                                                  string(basePath + "fragShader.glsl").c_str());
    camera = glm::vec3(0.0f, 0.0f, -8.0f);//相机一般朝向z轴的负方向，所以为了物体能显出来，z轴的值减去物体位置z轴的值要为一个负值
    cube = glm::vec3(0.0f, -2.0f, 0.0f);

    setupVertices();
}

void display(GLFWwindow *window, double currentTime) {
    glClear(GL_DEPTH_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(renderingProgram);

    //获取MV矩阵和投影矩阵的统一变量
    mvLoc = glGetUniformLocation(renderingProgram, "mv_matrix");//MV矩阵
    projLoc = glGetUniformLocation(renderingProgram, "proj_matrix");//投影矩阵
    //构建透视矩阵
    glfwGetFramebufferSize(window, &width, &height);
    fov = glm::radians(60.0f);
    aspect = (float) width / (float) height;

        pMat = glm::perspective(fov, aspect, 0.1f, 1000.0f);
        //构建视图矩阵、模型矩阵和MV矩阵
        vMat = glm::translate(glm::mat4(1.0f), camera);
    //静态模式还是动态模式
    bool dynamic = true;
    if (!dynamic) {
        mMat = glm::translate(glm::mat4(1.0f), cube);
    } else {
        //根据当前时间来计算x轴、y轴、z轴的变换
        cube = glm::vec3(sin(0.35f*currentTime)*2.0f,sin(0.35f*currentTime)*2.0f,sin(0.35f*currentTime)*2.0f);
        auto tMat = glm::translate(glm::mat4(1.0f), cube);
        float speed = 1.75f;
        auto rMat = glm::rotate(glm::mat4(1.0f), speed*(float)currentTime, glm::vec3(0.0f, 1.0f, 0.0f));
        rMat = glm::rotate(rMat, speed*(float)currentTime, glm::vec3(1.0f, 0.0f, 0.0f));
        rMat = glm::rotate(rMat, speed*(float)currentTime, glm::vec3(0.0f, 0.0f, 1.0f));
        mMat = rMat * tMat;
    }
        mvMat = vMat * mMat;

    //将透视矩阵和MV矩阵传递给着色器
    glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));
    //将VBO关联给顶点着色器中相应的顶点属性
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);
    glEnableVertexAttribArray(0);
    //调整OpenGL设置，绘制模型
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    //设置填充方式，因为每个面颜色一样，所以不易看出形状
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glDrawArrays(GL_TRIANGLES, 0, 36);
}

int main(void) {
    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    GLFWwindow *window = glfwCreateWindow(600, 600, "Chapter 4 - program 1a", NULL, NULL);
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