add_executable(ch17_anaglyph anaglyph/main.cpp
        anaglyph/ImportedModel.cpp
        anaglyph/Utils.cpp)
target_link_libraries(ch17_anaglyph ${LIBS})

add_executable(ch17_sideBySide sideBySide/main.cpp
        sideBySide/ImportedModel.cpp
        sideBySide/Utils.cpp)
target_link_libraries(ch17_sideBySide ${LIBS})

add_executable(ch17_distortionCorrection distortionCorrection/main.cpp
        distortionCorrection/ImportedModel.cpp
        distortionCorrection/Utils.cpp)
target_link_libraries(ch17_distortionCorrection ${LIBS})