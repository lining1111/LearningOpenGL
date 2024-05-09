#include <cmath>
#include <vector>
#include <glm/glm.hpp>

class Sphere {
private:
    int numVertices;
    int numIndices;
    std::vector<int> indices;
    std::vector<glm::vec3> vertices;//顶点数组
    std::vector<glm::vec2> texCoords;//纹理坐标数组
    std::vector<glm::vec3> normals;//法线数组
    std::vector<glm::vec3> tangents;//切线数组

    //prec 表示精度，体现为切片数量
    void init(int prec);

    float toRadians(float degrees);

public:
    Sphere();

    Sphere(int prec);

    int getNumVertices();

    int getNumIndices();

    std::vector<int> getIndices();

    std::vector<glm::vec3> getVertices();

    std::vector<glm::vec2> getTexCoords();

    std::vector<glm::vec3> getNormals();

    std::vector<glm::vec3> getTangents();
};