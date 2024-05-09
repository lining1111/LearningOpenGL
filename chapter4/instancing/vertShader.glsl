#version 430

layout (location = 0) in vec3 position;

uniform mat4 v_matrix;
uniform mat4 proj_matrix;
uniform float tf; //用于动画和放置立方体的时间因子

out vec4 varyingColor;

mat4 buildTranslate(float x, float y, float z) {
    mat4 trans = mat4(1.0, 0.0, 0.0, 0.0,
                      0.0, 1.0, 0.0, 0.0,
                      0.0, 0.0, 1.0, 0.0,
                      x, y, z, 1.0);
    return trans;
}

//  rotation around the X axis
mat4 buildRotateX(float rad) {
    mat4 xrot = mat4(1.0, 0.0, 0.0, 0.0,
                     0.0, cos(rad), -sin(rad), 0.0,
                     0.0, sin(rad), cos(rad), 0.0,
                     0.0, 0.0, 0.0, 1.0);
    return xrot;
}

//  rotation around the Y axis
mat4 buildRotateY(float rad) {
    mat4 yrot = mat4(cos(rad), 0.0, sin(rad), 0.0,
                     0.0, 1.0, 0.0, 0.0,
                     -sin(rad), 0.0, cos(rad), 0.0,
                     0.0, 0.0, 0.0, 1.0);
    return yrot;
}

//  rotation around the Z axis
mat4 buildRotateZ(float rad) {
    mat4 zrot = mat4(cos(rad), sin(rad), 0.0, 0.0,
                     -sin(rad), cos(rad), 0.0, 0.0,
                     0.0, 0.0, 1.0, 0.0,
                     0.0, 0.0, 0.0, 1.0);
    return zrot;
}


void main(void) {
    float i = gl_InstanceID + tf;//取值基于时间因子，但是对每个立方体示例也都是不同的
    //	float a = sin(203.0 * i/8000.0) * 403.0;	//when 100000 instances
    //	float b = cos(301.0 * i/4001.0) * 401.0;
    //	float c = sin(400.0 * i/6003.0) * 405.0;

    float a = sin(.35 * i) * 8.0;                // when 24 instances
    float b = cos(.52 * i) * 8.0;
    float c = sin(.70 * i) * 8.0;

    //构建旋转和平移矩阵，将会应用于当前立方体的模型矩阵
    mat4 localRotX = buildRotateX(1.75 * i);
    mat4 localRotY = buildRotateY(1.75 * i);
    mat4 localRotZ = buildRotateZ(1.75 * i);
    mat4 localTrans = buildTranslate(a, b, c);

    //构建模型矩阵，然后构建MV矩阵
    mat4 newM_matrix = localTrans * localRotX * localRotY * localRotZ;
    mat4 mv_matrix = v_matrix * newM_matrix;
    gl_Position = proj_matrix * mv_matrix * vec4(position, 1.0);//修改位置
    varyingColor = vec4(position, 1.0) * 0.5 + vec4(0.5, 0.5, 0.5, 0.5);//修改颜色
}
