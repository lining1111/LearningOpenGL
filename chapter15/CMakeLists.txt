##水平面
add_executable(ch15_surfaceSetup surfaceSetup/main.cpp
        surfaceSetup/Utils.cpp)
target_link_libraries(ch15_surfaceSetup ${LIBS})
##有顶有底
add_executable(ch15_geometry geometry/main.cpp
        geometry/Utils.cpp)
target_link_libraries(ch15_geometry ${LIBS})
##添加反射和折射
add_executable(ch15_reflectionRefraction reflectionRefraction/main.cpp
        reflectionRefraction/Utils.cpp)
target_link_libraries(ch15_reflectionRefraction ${LIBS})
##添加波浪
add_executable(ch15_noiseWaves noiseWaves/main.cpp
        noiseWaves/Utils.cpp)
target_link_libraries(ch15_noiseWaves ${LIBS})
##更多修正
add_executable(ch15_adjustments adjustments/main.cpp
        adjustments/Utils.cpp)
target_link_libraries(ch15_adjustments ${LIBS})
##添加动画
add_executable(ch15_animation animation/main.cpp
        animation/Utils.cpp)
target_link_libraries(ch15_animation ${LIBS})
##水下散焦
add_executable(ch15_caustics caustics/main.cpp
        caustics/Utils.cpp)
target_link_libraries(ch15_caustics ${LIBS})