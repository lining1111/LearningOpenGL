##雾
add_executable(ch14_fog fog/main.cpp
        fog/ImportedModel.cpp
        fog/Utils.cpp)
target_link_libraries(ch14_fog ${LIBS})
##混合
add_executable(ch14_blending blending/main.cpp
        blending/ImportedModel.cpp
        blending/Torus.cpp
        blending/Utils.cpp)
target_link_libraries(ch14_blending ${LIBS})
##裁剪
add_executable(ch14_clipping clipping/main.cpp
        clipping/Torus.cpp
        clipping/Utils.cpp)
target_link_libraries(ch14_clipping ${LIBS})
##3D纹理条纹
add_executable(ch14_stripes3Dtex stripes3Dtex/main.cpp
        stripes3Dtex/ImportedModel.cpp
        stripes3Dtex/Utils.cpp)
target_link_libraries(ch14_stripes3Dtex ${LIBS})
##3D纹理大理石
add_executable(ch14_marble marble/main.cpp
        marble/ImportedModel.cpp
        marble/Utils.cpp)
target_link_libraries(ch14_marble ${LIBS})
##3D纹理木质
add_executable(ch14_wood wood/main.cpp
        wood/ImportedModel.cpp
        wood/Utils.cpp)
target_link_libraries(ch14_wood ${LIBS})
##云
add_executable(ch14_clouds clouds/main.cpp
        clouds/HalfSphere.cpp
        clouds/Utils.cpp)
target_link_libraries(ch14_clouds ${LIBS})
##动态云
add_executable(ch14_cloudsChanging cloudsChanging/main.cpp
        cloudsChanging/HalfSphere.cpp
        cloudsChanging/Utils.cpp)
target_link_libraries(ch14_cloudsChanging ${LIBS})
##溶解
add_executable(ch14_dissolve dissolve/main.cpp
        dissolve/Sphere.cpp
        dissolve/Utils.cpp)
target_link_libraries(ch14_dissolve ${LIBS})