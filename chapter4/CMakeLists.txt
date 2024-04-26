add_executable(ch4_plainRedCube plainRedCube/main.cpp
        plainRedCube/Utils.cpp)
target_link_libraries(ch4_plainRedCube ${LIBS})

add_executable(ch4_interpolatedColors interpolatedColors/main.cpp
        interpolatedColors/Utils.cpp)
target_link_libraries(ch4_interpolatedColors ${LIBS})

add_executable(ch4_tumbling tumbling/main.cpp
        tumbling/Utils.cpp)
target_link_libraries(ch4_tumbling ${LIBS})

add_executable(ch4_multipleCubes multipleCubes/main.cpp
        multipleCubes/Utils.cpp)
target_link_libraries(ch4_multipleCubes ${LIBS})

add_executable(ch4_instancing instancing/main.cpp
        instancing/Utils.cpp)
target_link_libraries(ch4_instancing ${LIBS})

add_executable(ch4_multipleModels multipleModels/main.cpp
        multipleModels/Utils.cpp)
target_link_libraries(ch4_multipleModels ${LIBS})

add_executable(ch4_matrixStack matrixStack/main.cpp
        matrixStack/Utils.cpp)
target_link_libraries(ch4_matrixStack ${LIBS})
