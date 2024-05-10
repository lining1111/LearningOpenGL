#version 430

layout (local_size_x = 1) in;
layout (binding = 0, rgba8) uniform image2D output_texture;
float camera_pos = 5.0;

struct Ray {
    vec3 start;    // 光线原点
    vec3 dir;    // 归一化后的光线方向
};

struct Collision {
    float t;    // 在光线上距离碰撞位置的距离
    vec3 p;        // 碰撞点的全局坐标
    vec3 n;        // 碰撞点的表面法向量
    bool inside;    // 碰撞是否在穿过物体内表面向外离开物体时发生的
    int object_index;    // 碰撞到的物体索引
};

float sphere_radius = 2.5;
vec3 sphere_position = vec3(1.0, 0.0, -3.0);
vec3 sphere_color = vec3(1.0, 0.0, 0.0); // 球面颜色为红色

vec3 box_mins = vec3(-2.0, -2.0, 0.0);
vec3 box_maxs = vec3(-0.5, 1.0, 2.0);
vec3 box_color = vec3(0.0, 1.0, 0.0); // 立方体颜色为绿色



//------------------------------------------------------------------------------
// 检查光线r是否与立方体相交
// This implementation is based on the following algorithm:
// http://web.cse.ohio-state.edu/~shen.94/681/Site/Slides_files/basic_algo.pdf
//------------------------------------------------------------------------------
Collision intersect_box_object(Ray r) {
    // Calculate the box's world mins and maxs:
    vec3 t_min = (box_mins - r.start) / r.dir;
    vec3 t_max = (box_maxs - r.start) / r.dir;
    vec3 t_minDist = min(t_min, t_max);
    vec3 t_maxDist = max(t_min, t_max);
    float t_near = max(max(t_minDist.x, t_minDist.y), t_minDist.z);
    float t_far = min(min(t_maxDist.x, t_maxDist.y), t_maxDist.z);

    Collision c;
    c.t = t_near;
    c.inside = false;

    // If the ray is entering the box, t_near contains the farthest boundary of entry
    // If the ray is leaving the box, t_far contains the closest boundary of exit
    // The ray intersects the box if and only if t_near < t_far, and if t_far > 0.0

    // 如果光线未与立方体相交，返回负值作为t的值
    if (t_near >= t_far || t_far <= 0.0) {
        c.t = -1.0;
        return c;
    }

    float intersect_distance = t_near;
    vec3 plane_intersect_distances = t_minDist;

    // 如果t_near小于0,则光线从立方体内部开始，并离开立方体
    if (t_near < 0.0) {
        c.t = t_far;
        intersect_distance = t_far;
        plane_intersect_distances = t_maxDist;
        c.inside = true;
    }

    // 检查交点所处的边界
    int face_index = 0;

    if (intersect_distance == plane_intersect_distances.y) {
        face_index = 1;
    } else if (intersect_distance == plane_intersect_distances.z) {
        face_index = 2;
    }

    // 创建碰撞法向量
    c.n = vec3(0.0);
    c.n[face_index] = 1.0;

    // 如果从坐标轴负方向与立方体发生碰撞，则法向量需要取反
    if (r.dir[face_index] > 0.0) {
        c.n *= -1.0;
    }

    // 计算碰撞点的全局坐标
    c.p = r.start + c.t * r.dir;

    return c;
}

//------------------------------------------------------------------------------
// 检查光线r是否与球体相交
// This implementation is based on the following algorithm:
// http://web.cse.ohio-state.edu/~shen.94/681/Site/Slides_files/basic_algo.pdf
//------------------------------------------------------------------------------
Collision intersect_sphere_object(Ray r) {
    float qa = dot(r.dir, r.dir);
    float qb = dot(2 * r.dir, r.start - sphere_position);
    float qc = dot(r.start - sphere_position, r.start - sphere_position) - sphere_radius * sphere_radius;

    // Solving for qa * t^2 + qb * t + qc = 0
    float qd = qb * qb - 4 * qa * qc;

    Collision c;
    c.inside = false;

    // no solution in this case
    if (qd < 0.0) {
        c.t = -1.0;
        return c;
    }

    float t1 = (-qb + sqrt(qd)) / (2.0 * qa);
    float t2 = (-qb - sqrt(qd)) / (2.0 * qa);

    float t_near = min(t1, t2);
    float t_far = max(t1, t2);

    c.t = t_near;

    // sphere is behind the ray, no intersection
    if (t_far < 0.0) {
        c.t = -1.0;
        return c;
    }

    // the ray started inside the sphere
    if (t_near < 0.0) {
        c.t = t_far;
        c.inside = true;
    }

    c.p = r.start + c.t * r.dir;    // world position of the collision
    c.n = normalize(c.p - sphere_position);    // use the world position to compute the surface normal

    // if collision is leaving the sphere, flip the normal
    if (c.inside) {
        c.n *= -1.0;
    }
    return c;
}

//------------------------------------------------------------------------------
// 返回光线最近的碰撞
// object_index == -1 if no collision
// object_index == 1 if collision with sphere
// object_index == 2 if collision with box
//------------------------------------------------------------------------------
Collision get_closest_collision(Ray r) {
    Collision closest_collision, cSph, cBox;
    closest_collision.object_index = -1;

    cSph = intersect_sphere_object(r);
    cBox = intersect_box_object(r);

    if ((cSph.t > 0) && ((cSph.t < cBox.t) || (cBox.t < 0))) {
        closest_collision = cSph;
        closest_collision.object_index = 1;
    }
    if ((cBox.t > 0) && ((cBox.t < cSph.t) || (cSph.t < 0))) {
        closest_collision = cBox;
        closest_collision.object_index = 2;
    }
    return closest_collision;
}

//------------------------------------------------------------------------------
// This function casts a ray into the scene and returns the final color for a pixel
//------------------------------------------------------------------------------
vec3 raytrace(Ray r) {
    Collision c = get_closest_collision(r);
    if (c.object_index == -1) {
        return vec3(0.0);    // 如果没有碰撞返回黑色
    }
    if (c.object_index == 1) {
        return sphere_color;
    }
    if (c.object_index == 2) {
        return box_color;
    }
}

void main() {
    int width = int(gl_NumWorkGroups.x);
    int height = int(gl_NumWorkGroups.y);
    ivec2 pixel = ivec2(gl_GlobalInvocationID.xy);

    // 从像素空间转换到全局空间
    float x_pixel = 2.0 * pixel.x / width - 1.0;
    float y_pixel = 2.0 * pixel.y / height - 1.0;

    // 获取像素的全局光线
    Ray world_ray;
    world_ray.start = vec3(0.0, 0.0, camera_pos);
    vec4 world_ray_end = vec4(x_pixel, y_pixel, camera_pos - 1.0, 1.0);
    world_ray.dir = normalize(world_ray_end.xyz - world_ray.start);

    // 投射光线并与物体相交
    vec3 color = raytrace(world_ray);
    imageStore(output_texture, pixel, vec4(color, 1.0));
}