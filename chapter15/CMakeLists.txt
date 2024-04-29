add_executable(ch15_surfaceSetup surfaceSetup/main.cpp
        surfaceSetup/Utils.cpp)
target_link_libraries(ch15_surfaceSetup ${LIBS})

add_executable(ch15_geometry geometry/main.cpp
        geometry/Utils.cpp)
target_link_libraries(ch15_geometry ${LIBS})

add_executable(ch15_reflectionRefraction reflectionRefraction/main.cpp
        reflectionRefraction/Utils.cpp)
target_link_libraries(ch15_reflectionRefraction ${LIBS})

add_executable(ch15_noiseWaves noiseWaves/main.cpp
        noiseWaves/Utils.cpp)
target_link_libraries(ch15_noiseWaves ${LIBS})

add_executable(ch15_adjustments adjustments/main.cpp
        adjustments/Utils.cpp)
target_link_libraries(ch15_adjustments ${LIBS})

add_executable(ch15_animation animation/main.cpp
        animation/Utils.cpp)
target_link_libraries(ch15_animation ${LIBS})

add_executable(ch15_caustics caustics/main.cpp
        caustics/Utils.cpp)
target_link_libraries(ch15_caustics ${LIBS})