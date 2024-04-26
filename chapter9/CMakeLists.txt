add_executable(ch9_skyboxSimple skyboxSimple/main.cpp
        skyboxSimple/Torus.cpp
        skyboxSimple/Utils.cpp)
target_link_libraries(ch9_skyboxSimple ${LIBS})

add_executable(ch9_skyboxOpenGL skyboxOpenGL/main.cpp
        skyboxOpenGL/Torus.cpp
        skyboxOpenGL/Utils.cpp)
target_link_libraries(ch9_skyboxOpenGL ${LIBS})

add_executable(ch9_environmentMapping environmentMapping/main.cpp
        environmentMapping/Torus.cpp
        environmentMapping/Utils.cpp)
target_link_libraries(ch9_environmentMapping ${LIBS})
