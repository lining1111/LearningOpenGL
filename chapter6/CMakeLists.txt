## 顶点方式绘制球体
add_executable(ch6_sphere sphere/main.cpp
        sphere/Sphere.cpp
        sphere/Utils.cpp)
target_link_libraries(ch6_sphere ${LIBS})
## 索引方式绘制环面
add_executable(ch6_torus torus/main.cpp
        torus/Torus.cpp
        torus/Utils.cpp)
target_link_libraries(ch6_torus ${LIBS})
## 加载外部模型文件
add_executable(ch6_objLoaderShuttle objLoaderShuttle/main.cpp
        objLoaderShuttle/ImportedModel.cpp
        objLoaderShuttle/Utils.cpp)
target_link_libraries(ch6_objLoaderShuttle ${LIBS})