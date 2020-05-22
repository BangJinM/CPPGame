add_executable(Windows 
    GamePlatform-opengl.cpp
    ${PROJECT_SOURCE_DIR}/External/src/glad/src/glad.c
)
target_link_libraries(Windows Common)

target_include_directories(Windows PRIVATE "${PROJECT_SOURCE_DIR}/External/src/glad/include")

find_library(GLEW glfw3 PATHS ${MYGE_EXTERNAL_LIBRARY_PATH})
target_link_libraries(Windows ${GLEW})






find_package(OpenGL REQUIRED)

add_library(WindowsApplication WindowsApplication.cpp)

add_executable(Windows2 
    OpenGLApplication.cpp
    ${PROJECT_SOURCE_DIR}/External/src/glad/src/glad_wgl.c
)
target_link_libraries(Windows2 Common WindowsApplication ${OPENGL_LIBRARIES})

target_include_directories(Windows2 PRIVATE "${PROJECT_SOURCE_DIR}/External/src/glad/include")