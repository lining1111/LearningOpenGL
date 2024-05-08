//
// Created by lining on 2024/5/8.
//

//测试glm的矩阵运算
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>

using namespace std;

static void printOpenGLMat(glm::mat4 mat) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cout << mat[i][j] << " ";
        }
        cout << std::endl;
    }
}

static void printOpenGLVec(glm::vec4 vec) {
    cout << vec.x << " " << vec.y << " " << vec.z << " " << vec.w << std::endl;
}


void mat_opengl() {
    glm::vec4 point = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    //打印下原始点位
    cout << "point:" << endl;
    printOpenGLVec(point);

    //平移矩阵
    glm::mat4 mat4_1 = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    cout << "平移矩阵:" << endl;
    printOpenGLMat(mat4_1);
    glm::vec4 point_1 = mat4_1 * point;
    cout << "平移后的点位:" << endl;
    printOpenGLVec(point_1);

    //缩放矩阵
    glm::mat4 mat4_2 = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 0.5f));
    cout << "缩放矩阵:" << endl;
    printOpenGLMat(mat4_2);
    glm::vec4 point_2 = mat4_2 * point;
    cout << "缩放后的点位:" << endl;
    printOpenGLVec(point_2);

    //旋转矩阵
    glm::mat4 mat4_3 = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    cout << "旋转矩阵:" << endl;
    printOpenGLMat(mat4_3);
    glm::vec4 point_3 = mat4_3 * point;
    cout << "旋转后的点位:" << endl;
    printOpenGLVec(point_3);
}

static void printEigenMat(Eigen::Matrix4f mat) {
    cout << mat.matrix() << endl;
}

static void printEigenVec(Eigen::Vector4f vec) {
    cout << vec.matrix() << endl;
}

void mat_eigen3() {
    Eigen::Vector4f point(1, 1, 1, 1);

    //打印下原始点位
    cout << "point:" << endl;
    printEigenVec(point);

    //平移矩阵
    Eigen::Matrix4f mat4_1 = Eigen::Matrix4f::Identity();
    mat4_1.block<3, 1>(0, 3) = Eigen::Vector3f(1, 0, 0);
    cout << "平移矩阵:" << endl;
    printEigenMat(mat4_1);
    Eigen::Vector4f point_1 = mat4_1 * point;
    cout << "平移后的点位:" << endl;
    printEigenVec(point_1);

    //缩放矩阵
    Eigen::Matrix4f mat4_2 = Eigen::Matrix4f::Identity();
    mat4_2.block<3, 3>(0, 0) = Eigen::Matrix3f::Identity() * 0.5;
    cout << "缩放矩阵:" << endl;
    printEigenMat(mat4_2);
    Eigen::Vector4f point_2 = mat4_2 * point;
    cout << "缩放后的点位:" << endl;
    printEigenVec(point_2);

    //旋转矩阵
    Eigen::Matrix4f mat4_3 = Eigen::Matrix4f::Identity();
    mat4_3.block<3, 3>(0, 0) = Eigen::AngleAxisf(M_PI / 2, Eigen::Vector3f::UnitZ()) *
                               Eigen::AngleAxisf(0, Eigen::Vector3f::UnitY()) *
                               Eigen::AngleAxisf(0, Eigen::Vector3f::UnitX()).matrix();
    cout << "旋转矩阵:" << endl;
    printEigenMat(mat4_3);
    Eigen::Vector4f point_3 = mat4_3 * point;
    cout << "旋转后的点位:" << endl;
    printEigenVec(point_3);

}

int main(int argc, char **argv) {
    mat_opengl();

    mat_eigen3();

    return 0;
}