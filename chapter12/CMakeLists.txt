add_executable(ch12_tessellationGridOnly tessellationGridOnly/main.cpp
        tessellationGridOnly/Utils.cpp)
target_link_libraries(ch12_tessellationGridOnly ${LIBS})

add_executable(ch12_tessellationBezier tessellationBezier/main.cpp
        tessellationBezier/Utils.cpp)
target_link_libraries(ch12_tessellationBezier ${LIBS})

add_executable(ch12_tessHeightMappedInstanced tessHeightMappedInstanced/main.cpp
        tessHeightMappedInstanced/Utils.cpp)
target_link_libraries(ch12_tessHeightMappedInstanced ${LIBS})

add_executable(ch12_tessHeightMappedInstWLighting tessHeightMappedInstWLighting/main.cpp
        tessHeightMappedInstWLighting/Utils.cpp)
target_link_libraries(ch12_tessHeightMappedInstWLighting ${LIBS})

add_executable(ch12_tessHeightMappedInstancedLOD tessHeightMappedInstancedLOD/main.cpp
        tessHeightMappedInstancedLOD/Utils.cpp)
target_link_libraries(ch12_tessHeightMappedInstancedLOD ${LIBS})