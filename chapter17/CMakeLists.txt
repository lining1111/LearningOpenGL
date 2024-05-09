##雾的色差渲染
add_executable(ch17_anaglyph anaglyph/main.cpp
        anaglyph/ImportedModel.cpp
        anaglyph/Utils.cpp)
target_link_libraries(ch17_anaglyph ${LIBS})
##雾的并排渲染
add_executable(ch17_sideBySide sideBySide/main.cpp
        sideBySide/ImportedModel.cpp
        sideBySide/Utils.cpp)
target_link_libraries(ch17_sideBySide ${LIBS})
##启用镜头畸变校正的并排渲染
add_executable(ch17_distortionCorrection distortionCorrection/main.cpp
        distortionCorrection/ImportedModel.cpp
        distortionCorrection/Utils.cpp)
target_link_libraries(ch17_distortionCorrection ${LIBS})