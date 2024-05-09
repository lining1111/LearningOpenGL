#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include "ImportedModel.h"
#include "Utils.h"

using namespace std;

float toRadians(float degrees) { return (degrees * 2.0f * 3.14159f) / 360.0f; }

#define numVAOs 1
#define numVBOs 3

float cameraX, cameraY, cameraZ;
float objLocX, objLocY, objLocZ;
GLuint renderingProgram;
GLuint vao[numVAOs];
GLuint vbo[numVBOs];

GLuint stripesTexture;
const int texHeight = 200;
const int texWidth = 200;
const int texDepth = 200;
double tex3Dpattern[texHeight][texWidth][texDepth];

// variable allocation for display
GLuint mvLoc, projLoc;
int width, height;
float aspect;
glm::mat4 pMat, vMat, mMat, mvMat;

auto basePath = string("chapter14/stripes3Dtex/");
ImportedModel dolphinObj(string(basePath + "dolphinLowPoly.obj").c_str());
int numDolphinVertices;

// 3D Texture section

void fillDataArray(GLubyte data[]) {
    for (int i = 0; i < texHeight; i++) {
        for (int j = 0; j < texWidth; j++) {
            for (int k = 0; k < texDepth; k++) {
                if (tex3Dpattern[i][j][k] == 1.0) {
                    // yellow color
                    data[i * (texWidth * texHeight * 4) + j * (texHeight * 4) + k * 4 + 0] = (GLubyte) 255; //red
                    data[i * (texWidth * texHeight * 4) + j * (texHeight * 4) + k * 4 + 1] = (GLubyte) 255; //green
                    data[i * (texWidth * texHeight * 4) + j * (texHeight * 4) + k * 4 + 2] = (GLubyte) 0; //blue
                    data[i * (texWidth * texHeight * 4) + j * (texHeight * 4) + k * 4 + 3] = (GLubyte) 0; //alpha
                } else {
                    // blue color
                    data[i * (texWidth * texHeight * 4) + j * (texHeight * 4) + k * 4 + 0] = (GLubyte) 0; //red
                    data[i * (texWidth * texHeight * 4) + j * (texHeight * 4) + k * 4 + 1] = (GLubyte) 0; //green
                    data[i * (texWidth * texHeight * 4) + j * (texHeight * 4) + k * 4 + 2] = (GLubyte) 255; //blue
                    data[i * (texWidth * texHeight * 4) + j * (texHeight * 4) + k * 4 + 3] = (GLubyte) 0; //alpha
                }
            }
        }
    }
}

int build3DTexture() {
    GLuint textureID;
    GLubyte *data = new GLubyte[texHeight * texWidth * texDepth * 4];

    fillDataArray(data);

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_3D, textureID);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexStorage3D(GL_TEXTURE_3D, 1, GL_RGBA8, texWidth, texHeight, texDepth);
    glTexSubImage3D(GL_TEXTURE_3D, 0, 0, 0, 0, texWidth, texHeight, texDepth, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8_REV,
                    data);

    delete[] data;
    return textureID;
}

void generate3Dpattern() {
    for (int x = 0; x < texHeight; x++) {
        for (int y = 0; y < texWidth; y++) {
            for (int z = 0; z < texDepth; z++) {
                if ((y / 10) % 2 == 0)
                    tex3Dpattern[x][y][z] = 0.0;
                else
                    tex3Dpattern[x][y][z] = 1.0;
            }
        }
    }
}

/*
//  replace above function with the one below
//	to change the stripes to a checkerboard.

void generate3Dpattern() {
	int xStep, yStep, zStep, sumSteps;
	for (int offsetX = 0; offsetX < texWidth; offsetX++) {
		for (int y = 0; y < texHeight; y++) {
			for (int z = 0; z < texDepth; z++) {
				xStep = (offsetX / 10) % 2;
				yStep = (y / 10) % 2;
				zStep = (z / 10) % 2;
				sumSteps = xStep + yStep + zStep;
				if ((sumSteps % 2) == 0)
					tex3Dpattern[offsetX][y][z] = 0.0;
				else
					tex3Dpattern[offsetX][y][z] = 1.0;
			}
		}
	}
}
*/

void setupVertices(void) {
    numDolphinVertices = dolphinObj.getNumVertices();
    std::vector<glm::vec3> vert = dolphinObj.getVertices();
    std::vector<glm::vec2> tex = dolphinObj.getTextureCoords();
    std::vector<glm::vec3> norm = dolphinObj.getNormals();

    std::vector<float> pvalues;
    std::vector<float> tvalues;
    std::vector<float> nvalues;

    for (int i = 0; i < numDolphinVertices; i++) {
        pvalues.push_back((vert[i]).x);
        pvalues.push_back((vert[i]).y);
        pvalues.push_back((vert[i]).z);
        tvalues.push_back((tex[i]).s);
        tvalues.push_back((tex[i]).t);
        nvalues.push_back((norm[i]).x);
        nvalues.push_back((norm[i]).y);
        nvalues.push_back((norm[i]).z);
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
}

void init(GLFWwindow *window) {
    renderingProgram = Utils::createShaderProgram(string(basePath + "vertShader.glsl").c_str(),
                                                  string(basePath + "fragShader.glsl").c_str());
    cameraX = 0.0f;
    cameraY = 0.0f;
    cameraZ = 2.0f;
    objLocX = 0.0f;
    objLocY = 0.0f;
    objLocZ = 0.0f;

    glfwGetFramebufferSize(window, &width, &height);
    aspect = (float) width / (float) height;
    pMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f);

    setupVertices();

    generate3Dpattern();
    stripesTexture = build3DTexture();
}

void display(GLFWwindow *window, double currentTime) {
    glClear(GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(renderingProgram);

    mvLoc = glGetUniformLocation(renderingProgram, "mv_matrix");
    projLoc = glGetUniformLocation(renderingProgram, "proj_matrix");

    vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ));
    mMat = glm::translate(glm::mat4(1.0f), glm::vec3(objLocX, objLocY, objLocZ));
    mMat = glm::rotate(mMat, toRadians(15.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    mMat = glm::rotate(mMat, toRadians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    mvMat = vMat * mMat;

    glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_3D, stripesTexture);

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glDrawArrays(GL_TRIANGLES, 0, numDolphinVertices);
}

void window_size_callback(GLFWwindow *win, int newWidth, int newHeight) {
    aspect = (float) newWidth / (float) newHeight;
    glViewport(0, 0, newWidth, newHeight);
    pMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f);
}

int main(void) {
    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    GLFWwindow *window = glfwCreateWindow(600, 600, "Chapter 14 - program 4", NULL, NULL);
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK) {
        exit(EXIT_FAILURE);
    }
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