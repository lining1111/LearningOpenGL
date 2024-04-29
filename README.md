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

## chapter2

    