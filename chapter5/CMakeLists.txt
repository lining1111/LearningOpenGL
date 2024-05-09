##简单贴图
add_executable(ch5_texturedPyramid texturedPyramid/main.cpp
        texturedPyramid/Utils.cpp)
target_link_libraries(ch5_texturedPyramid ${LIBS})
##多级渐远贴图,和上面比物体动起来了
add_executable(ch5_texturedPyramidMipmapAniso texturedPyramidMipmapAniso/main.cpp
        texturedPyramidMipmapAniso/Utils.cpp)
target_link_libraries(ch5_texturedPyramidMipmapAniso ${LIBS})