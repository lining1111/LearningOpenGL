# 计算机图形学编程(使用OpenGL和C++)(第2版)

    mesa-utils
    glxinfo | grep "OpenGL" 查看OpenGL相关版本信息
    
    OpenGL4.3及以上版本    虚拟机的ubuntu在使用的时候，需要VMware17版本(支持OpenGL4.3)，ubuntu22.04版本及以上
    SOIL2 地址 https://github.com/SpartanJ/SOIL2
    注意这个SOIL2的库，就要用libs/SOIL2下的，从github上下载的1-20，有问题

## 首次跑demo的注意事项

    由于OpenGL是图形编程的库，所以涉及硬件性能，同时由于程序是运行在ubuntu虚拟机上，电脑的性能是有打折的，有些渲染出来会很耗时
    耗时长的有：
    ch14_clouds、ch14_cloudsChangeing、ch14_marble、ch14_wood
    ch15_adjustments、ch15_animation、ch15_caustics、ch15_noiseWaves、ch15_reflectionRefraction
    其中ch15_noiseWaves、ch15_reflectionRefraction最耗时,耗时到在IDE中debug很卡出去
    ch16_combiningReflectionRefraction、ch16_nonAxisBox、ch16_objectDefinition、ch16_plane、ch16_rayCasting、ch16_lightingShadows、ch16_recursion、ch16_singleReflection、ch16_singleRefraction、ch16_skybox、ch16_texture会因为在OpenGL430上跑gl_FragColor出现问题(fragShafer.glsl中)
    ch17_anaglyph、ch17_distortionCorrection会有一卡一卡的

    ch14_dissolve是表演溶解的，会进行的很快

    20240429 ch16中多的问题，可能是现在的知识还不到位，后面学习到了希望能解决吧

## 概念

    OpenGL库分类：
    OpenGL/GLSL
    freeglut 窗口管理库
    glew OpenGL扩展库
    glm OpenGL数学库
    SOIL2 纹理库

    OpenGL编程，一部分由C++实现，进行OpenGL调用，一部分由GLSL实现，进行OpenGL渲染。
    C++/OpenGL应用、GLSL模块和硬件一起用来生成3D图形输出。
    GLSL是一种着色器语言，主要运行在GPU上。
    点、线、三角形，叫做图元，OpenGL中，图元是渲染的基本单位。多数3模型是由三角形组成的。
    OpenGL中，图元是渲染的基本单位。多数3模型是由三角形组成的。
    顶点着色器赋予程序员一次操作一个顶点的能力，
    片段着色器赋予程序员一次操作一个像素的能力。
    几何着色器赋予程序员一次操作一个图元的能力。
    vertex      vertShader  所有顶点着色器的主要目标都是将顶点发送给管线
    fragment    fragShader  所有片段着色器的主要目标都是给为了要展示的像素赋予颜色
    geometry    geomShader  几何着色器的主要目标就是处理图元
    tessC       tessCShader 细分控制着色器的主要目标就是处理图元
    tessE       tessEShader 细分计算着色器的主要目标就是处理图元

    在顶点处理和像素处理中间，会经过光栅化阶段，将图元转换为像素。
    
    当绘制场景中各种对象时，片段着色器会生成像素颜色，像素颜色会存放到颜色缓冲区中，而最终的颜色缓冲区会被写到屏幕上。
    当多个对象占据颜色缓冲区中的相同像素时，必须根据最终接近观察者的对象来确定要保留的像素颜色。

    VBO 顶点缓冲对象
    VAO 顶点数组对象
    基本图元类型:涵盖点-线-面(图元方向默认是逆时针的，可以修改为顺时针)
    GL_POINTS           单个顶点集，创建单个点
    GL_LINES            多组双顶点线段，创建线段
    GL_LINE_STRIP       不闭合折线，创建线段
    GL_LINE_LOOP        闭合折线，创建线段
    GL_POLYGON          单个简单填充凸多边形，构建一个凸多边形
    GL_QUADS            多组独立填充四边形，创建四边形
    GL_QUAD_STRIP       连续填充四边形，创建四边形
    GL_TRIANGLES        多组独立填充三角形，创建三角形
    GL_TRIANGLE_STRIP   线型连续填充三角形，创建三角形
    GL_TRIANGLE_FAN     扇型连续填充三角形，创建三角形

    栅格化：为了显示3个顶点确定的三角形需要绘制的所有像素的位置
    栅格化开始，先对三角形的每对顶点进行插值，得到三角形上的所有顶点，
    然后将三角形上的所有顶点，映射到屏幕上，得到三角形上的所有像素，
    然后将三角形上的所有像素，映射到颜色缓冲区中，最后将颜色缓冲区中的所有像素，映射到屏幕上。
    插值：插值是用来计算一个点在一条线段上的位置的算法。
    GL_FILL     默认填充方式
    GL_LINE     呈现线框模型
    GL_POINT    用点绘制图形
    
    glsl语言中数据类型包括：
    基础数据类型：int、float、double、uint、bool等
    容器类型：vec：
            mat：
    着色器通信，每个阶段的着色器都是独立的程序，前一个的输出是后面一个的输入。
    从cpu中应用向GPU发送数据、从顶点着色器向片段着色器发生数据等。主要包括下面的方式
    uniform：从cpu应用向gpu发送数据
    in/out:上个阶段着色器的输出结果是下个阶段着色器的输入
    layout:从cpu应用向gpu中的顶点着色器传输顶点的多个维度数据(位置、颜色、纹理坐标、法向量等)

    工程代码中，基础类：
    Utils:错误检测、读取着色器
        ---支持顶点着色器、片段着色器
        static GLuint createShaderProgram(const char *vp, const char *fp);
        ---支持顶点着色器、几何着色器、片段着色器
        static GLuint createShaderProgram(const char *vp, const char *gp, const char *fp);
        ---支持顶点着色器、曲面细分着色器(2)、片段着色器
        static GLuint createShaderProgram(const char *vp, const char *tCS, const char *tES, const char *fp);
        ---支持顶点着色器、曲面细分着色器(2)、几何着色器、片段着色器
        static GLuint createShaderProgram(const char *vp, const char *tCS, const char *tES, char *gp, const char *fp);
    Torus:环面类
    Sphere:球体类
    Cube:立方体类
    ImportedModel:导入模型类
    
    

    **OpenGL的难点除了按照套路来完成顶点、片段、加载纹理等，还需要在动态变换时，对矩阵有深刻的理解。**

## chapter2

    介绍基本单元的使用，很粗略，目的建立一个基本的概念。

## chapter3

    计算机图形学使用了大量的数学知识，尤其是矩阵和线性代数。

## chapter4

## chapter5

## chapter6

    .obj文件的查看，ubuntu安装blender,apt安装就行，clion上安装插件 Wavefront OBJ，即可在clion上完成.obj文件的预览
    blender使用说明 https://docs.blender.org/manual/zh-hans/2.92/getting_started/index.html
    开源的.obj文件下载 https://www.blender.org/download/demo-files/

## chapter7

    A:环境光反射
    D:漫反射
    S:镜面反射
    Gouraud着色:平滑着色算法，由于使用了3D图形管线中的自动插值渲染，因此它特别适用于现代显卡。
    Phong着色:
    Blinn-Phong着色:

## chapter8

## chapter9

## chapter10

## chapter12

## chapter13

## chapter14

## chapter15

## chapter16

## chapter17


    