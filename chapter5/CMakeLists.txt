add_executable(ch5_texturedPyramid texturedPyramid/main.cpp
        texturedPyramid/Utils.cpp)
target_link_libraries(ch5_texturedPyramid ${LIBS})

add_executable(ch5_texturedPyramidMipmapAniso texturedPyramidMipmapAniso/main.cpp
        texturedPyramidMipmapAniso/Utils.cpp)
target_link_libraries(ch5_texturedPyramidMipmapAniso ${LIBS})