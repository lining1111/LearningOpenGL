add_executable(ch13_geomModInflate geomModInflate/main.cpp
        geomModInflate/Torus.cpp
        geomModInflate/Utils.cpp)
target_link_libraries(ch13_geomModInflate ${LIBS})

add_executable(ch13_geomModExplodeNoBackFaces geomModExplodeNoBackFaces/main.cpp
        geomModExplodeNoBackFaces/Torus.cpp
        geomModExplodeNoBackFaces/Utils.cpp)
target_link_libraries(ch13_geomModExplodeNoBackFaces ${LIBS})

add_executable(ch13_geomModExplodeWithBackFaces geomModExplodeWithBackFaces/main.cpp
        geomModExplodeWithBackFaces/Torus.cpp
        geomModExplodeWithBackFaces/Utils.cpp)
target_link_libraries(ch13_geomModExplodeWithBackFaces ${LIBS})

add_executable(ch13_geometryDel geometryDel/main.cpp
        geometryDel/Torus.cpp
        geometryDel/Utils.cpp)
target_link_libraries(ch13_geometryDel ${LIBS})

add_executable(ch13_geometryAdd geometryAdd/main.cpp
        geometryAdd/Torus.cpp
        geometryAdd/Utils.cpp)
target_link_libraries(ch13_geometryAdd ${LIBS})

add_executable(ch13_geometryChange geometryChange/main.cpp
        geometryChange/Torus.cpp
        geometryChange/Utils.cpp)
target_link_libraries(ch13_geometryChange ${LIBS})