add_executable(ch6_sphere sphere/main.cpp
        sphere/Sphere.cpp
        sphere/Utils.cpp)
target_link_libraries(ch6_sphere ${LIBS})

add_executable(ch6_torus torus/main.cpp
        torus/Torus.cpp
        torus/Utils.cpp)
target_link_libraries(ch6_torus ${LIBS})

add_executable(ch6_objLoaderShuttle objLoaderShuttle/main.cpp
        objLoaderShuttle/ImportedModel.cpp
        objLoaderShuttle/Utils.cpp)
target_link_libraries(ch6_objLoaderShuttle ${LIBS})