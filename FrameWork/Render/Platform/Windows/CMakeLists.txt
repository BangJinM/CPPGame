
SET(FRAMEWORK_RENDER_PLATFORM_WINDOWS_HEADER 
Render/Platform/Windows/GamePlatform-opengl.h
Render/Platform/Windows/WindowsConfig.h
Render/Platform/Windows/InputManagerWindows.h
Render/Platform/Windows/Shader.h
Render/Platform/Windows/OpenGLShaderManager.h
Render/Platform/Windows/GraphicsManager.h
Render/Platform/Windows/imgui_impl_glfw.h
Render/Platform/Windows/imgui_impl_opengl3.h
)

SET(FRAMEWORK_RENDER_PLATFORM_WINDOWS_SRC 
Render/Platform/Windows/Shader.cpp
Render/Platform/Windows/GamePlatform-opengl.cpp
Render/Platform/Windows/InputManagerWindows.cpp
Render/Platform/Windows/GraphicsManager.cpp
Render/Platform/Windows/imgui_impl_glfw.cpp
Render/Platform/Windows/imgui_impl_opengl3.cpp
Render/Platform/Windows/OpenGLShaderManager.cpp
)

list(APPEND FRAMEWORK_HEADER ${FRAMEWORK_RENDER_PLATFORM_WINDOWS_HEADER})
list(APPEND FRAMEWORK_SRC ${FRAMEWORK_RENDER_PLATFORM_WINDOWS_SRC})

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

link_libraries(imgui::imgui glfw glad::glad)