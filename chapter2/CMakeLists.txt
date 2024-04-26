add_executable(ch2_background background/main.cpp)
target_link_libraries(ch2_background ${LIBS})

add_executable(ch2_point point/main.cpp)
target_link_libraries(ch2_point ${LIBS})

add_executable(ch2_errChecking errChecking/main.cpp)
target_link_libraries(ch2_errChecking ${LIBS})

add_executable(ch2_files files/main.cpp)
target_link_libraries(ch2_files ${LIBS})

add_executable(ch2_triangle triangle/main.cpp)
target_link_libraries(ch2_triangle ${LIBS})

add_executable(ch2_animation animation/main.cpp
        animation/Utils.cpp)
target_link_libraries(ch2_animation ${LIBS})

add_executable(ch2_supplemental_queryingOpenGL supplemental_queryingOpenGL/main.cpp)
target_link_libraries(ch2_supplemental_queryingOpenGL ${LIBS})