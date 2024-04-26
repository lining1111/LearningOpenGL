add_executable(ch16_computeShader computeShader/main.cpp
        computeShader/Utils.cpp)
target_link_libraries(ch16_computeShader ${LIBS})

add_executable(ch16_rayCasting rayCasting/main.cpp
        rayCasting/Utils.cpp)
target_link_libraries(ch16_rayCasting ${LIBS})

add_executable(ch16_lightingShadows lightingShadows/main.cpp
        lightingShadows/Utils.cpp)
target_link_libraries(ch16_lightingShadows ${LIBS})

add_executable(ch16_nonAxisBox nonAxisBox/main.cpp
        nonAxisBox/Utils.cpp)
target_link_libraries(ch16_nonAxisBox ${LIBS})

add_executable(ch16_texture texture/main.cpp
        texture/Utils.cpp)
target_link_libraries(ch16_texture ${LIBS})

add_executable(ch16_skybox skybox/main.cpp
        skybox/Utils.cpp)
target_link_libraries(ch16_skybox ${LIBS})

add_executable(ch16_plane plane/main.cpp
        plane/Utils.cpp)
target_link_libraries(ch16_plane ${LIBS})

add_executable(ch16_singleReflection singleReflection/main.cpp
        singleReflection/Utils.cpp)
target_link_libraries(ch16_singleReflection ${LIBS})

add_executable(ch16_singleRefraction singleRefraction/main.cpp
        singleRefraction/Utils.cpp)
target_link_libraries(ch16_singleRefraction ${LIBS})

add_executable(ch16_combiningReflectionRefraction combiningReflectionRefraction/main.cpp
        combiningReflectionRefraction/Utils.cpp)
target_link_libraries(ch16_combiningReflectionRefraction ${LIBS})

add_executable(ch16_recursion recursion/main.cpp
        recursion/Utils.cpp)
target_link_libraries(ch16_recursion ${LIBS})

add_executable(ch16_objectDefinition objectDefinition/main.cpp
        objectDefinition/Utils.cpp)
target_link_libraries(ch16_objectDefinition ${LIBS})