##过程式凹凸贴图
add_executable(ch10_procBump procBump/main.cpp
        procBump/Torus.cpp
        procBump/Utils.cpp)
target_link_libraries(ch10_procBump ${LIBS})
##法线贴图
add_executable(ch10_normalMapping normalMapping/main.cpp
        normalMapping/Sphere.cpp
        normalMapping/Utils.cpp)
target_link_libraries(ch10_normalMapping ${LIBS})
##纹理加法线贴图
add_executable(ch10_texturePlusNormal texturePlusNormal/main.cpp
        texturePlusNormal/Sphere.cpp
        texturePlusNormal/Utils.cpp)
target_link_libraries(ch10_texturePlusNormal ${LIBS})
##高度贴图
add_executable(ch10_heightMappedTerrain heightMappedTerrain/main.cpp
        heightMappedTerrain/ImportedModel.cpp
        heightMappedTerrain/Utils.cpp)
target_link_libraries(ch10_heightMappedTerrain ${LIBS})
##在顶点着色器中进行高度贴图
add_executable(ch10_sphereVertexHeightMap sphereVertexHeightMap/main.cpp
        sphereVertexHeightMap/Sphere.cpp
        sphereVertexHeightMap/Utils.cpp)
target_link_libraries(ch10_sphereVertexHeightMap ${LIBS})
