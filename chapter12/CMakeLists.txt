##基本曲面细分器网格
add_executable(ch12_tessellationGridOnly tessellationGridOnly/main.cpp
        tessellationGridOnly/Utils.cpp)
target_link_libraries(ch12_tessellationGridOnly ${LIBS})
##贝塞尔曲面的曲面细分
add_executable(ch12_tessellationBezier tessellationBezier/main.cpp
        tessellationBezier/Utils.cpp)
target_link_libraries(ch12_tessellationBezier ${LIBS})
##实例化的地形曲面细分
add_executable(ch12_tessHeightMappedInstanced tessHeightMappedInstanced/main.cpp
        tessHeightMappedInstanced/Utils.cpp)
target_link_libraries(ch12_tessHeightMappedInstanced ${LIBS})
##带光照的实例化地形曲面细分
add_executable(ch12_tessHeightMappedInstWLighting tessHeightMappedInstWLighting/main.cpp
        tessHeightMappedInstWLighting/Utils.cpp)
target_link_libraries(ch12_tessHeightMappedInstWLighting ${LIBS})
##控制细节的
add_executable(ch12_tessHeightMappedInstancedLOD tessHeightMappedInstancedLOD/main.cpp
        tessHeightMappedInstancedLOD/Utils.cpp)
target_link_libraries(ch12_tessHeightMappedInstancedLOD ${LIBS})