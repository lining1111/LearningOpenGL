##建立一个立方体
add_executable(ch4_plainRedCube plainRedCube/main.cpp
        plainRedCube/Utils.cpp)
target_link_libraries(ch4_plainRedCube ${LIBS})
##改变立方体的颜色
add_executable(ch4_interpolatedColors interpolatedColors/main.cpp
        interpolatedColors/Utils.cpp)
target_link_libraries(ch4_interpolatedColors ${LIBS})
##改变立方体的位置
add_executable(ch4_tumbling tumbling/main.cpp
        tumbling/Utils.cpp)
target_link_libraries(ch4_tumbling ${LIBS})
##多个立方体
add_executable(ch4_multipleCubes multipleCubes/main.cpp
        multipleCubes/Utils.cpp)
target_link_libraries(ch4_multipleCubes ${LIBS})
##实例化
add_executable(ch4_instancing instancing/main.cpp
        instancing/Utils.cpp)
target_link_libraries(ch4_instancing ${LIBS})
##多个模型 立方体和四棱锥
add_executable(ch4_multipleModels multipleModels/main.cpp
        multipleModels/Utils.cpp)
target_link_libraries(ch4_multipleModels ${LIBS})
##矩阵栈
add_executable(ch4_matrixStack matrixStack/main.cpp
        matrixStack/Utils.cpp)
target_link_libraries(ch4_matrixStack ${LIBS})
