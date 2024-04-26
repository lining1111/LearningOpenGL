add_executable(ch10_procBump procBump/main.cpp
        procBump/Torus.cpp
        procBump/Utils.cpp)
target_link_libraries(ch10_procBump ${LIBS})

add_executable(ch10_normalMapping normalMapping/main.cpp
        normalMapping/Sphere.cpp
        normalMapping/Utils.cpp)
target_link_libraries(ch10_normalMapping ${LIBS})

add_executable(ch10_texturePlusNormal texturePlusNormal/main.cpp
        texturePlusNormal/Sphere.cpp
        texturePlusNormal/Utils.cpp)
target_link_libraries(ch10_texturePlusNormal ${LIBS})

add_executable(ch10_heightMappedTerrain heightMappedTerrain/main.cpp
        heightMappedTerrain/ImportedModel.cpp
        heightMappedTerrain/Utils.cpp)
target_link_libraries(ch10_heightMappedTerrain ${LIBS})

add_executable(ch10_sphereVertexHeightMap sphereVertexHeightMap/main.cpp
        sphereVertexHeightMap/Sphere.cpp
        sphereVertexHeightMap/Utils.cpp)
target_link_libraries(ch10_sphereVertexHeightMap ${LIBS})
