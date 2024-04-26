add_executable(ch7_lightingADS lightingADS/main.cpp
        lightingADS/Torus.cpp
        lightingADS/Utils.cpp)
target_link_libraries(ch7_lightingADS ${LIBS})
