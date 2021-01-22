set(RHI_HEADER 
    Shader.h
    OpenGLCoinfig.h
    OpenGLShaderManager.h
    GraphicsManager.h
    imgui_impl_glfw.h
    imgui_impl_opengl3.h
)
set(RHI_SRC 
    Shader.cpp
    OpenGLShaderManager.cpp
    GraphicsManager.cpp
    imgui_impl_glfw.cpp
    imgui_impl_opengl3.cpp
)

add_library(RHI
    ${RHI_HEADER}
    ${RHI_SRC}
)

include_directories("${PROJECT_SOURCE_DIR}/RHI/OpenGL")
find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

target_link_libraries(RHI PRIVATE glad::glad)
target_link_libraries(RHI PRIVATE glfw )
