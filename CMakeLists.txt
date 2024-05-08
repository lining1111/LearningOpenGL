cmake_minimum_required(VERSION 3.27)
project(LearningOpenGL)

set(CMAKE_CXX_STANDARD 11)

include_directories(libs)
link_directories(${PROJECT_SOURCE_DIR}/libs/SOIL2/)

set(LIBS m z pthread
        GLEW glfw GL GLU glut soil2-debug.a)

add_executable(LearningOpenGL main.cpp)
target_link_libraries(LearningOpenGL ${LIBS})

## chapter2
add_subdirectory(chapter2)
## chapter3
add_subdirectory(chapter3)
## chapter4
add_subdirectory(chapter4)
## chapter5
add_subdirectory(chapter5)
## chapter6
add_subdirectory(chapter6)
## chapter7
add_subdirectory(chapter7)
## chapter8
add_subdirectory(chapter8)
## chapter9
add_subdirectory(chapter9)
## chapter10
add_subdirectory(chapter10)
## chapter12
add_subdirectory(chapter12)
## chapter13
add_subdirectory(chapter13)
## chapter14
add_subdirectory(chapter14)
## chapter15
add_subdirectory(chapter15)
## chapter16
add_subdirectory(chapter16)
## chapter17
add_subdirectory(chapter17)