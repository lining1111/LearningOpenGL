## 添加阴影
add_executable(ch8_shadowMapping shadowMapping/main.cpp
        shadowMapping/Torus.cpp
        shadowMapping/ImportedModel.cpp
        shadowMapping/Utils.cpp)
target_link_libraries(ch8_shadowMapping ${LIBS})
## 添加软阴影
add_executable(ch8_softShadowsPCF softShadowsPCF/main.cpp
        softShadowsPCF/Torus.cpp
        softShadowsPCF/ImportedModel.cpp
        softShadowsPCF/Utils.cpp)
target_link_libraries(ch8_softShadowsPCF ${LIBS})