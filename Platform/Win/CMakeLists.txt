add_executable(Win 
    GamePlatform-opengl.cpp
    ${PROJECT_SOURCE_DIR}/External/src/glad/src/glad.c
)
target_link_libraries(Win Common)

target_include_directories(Win PRIVATE "${PROJECT_SOURCE_DIR}/External/src/glad/include")

find_library(GLEW glfw3 PATHS ${MYGE_EXTERNAL_LIBRARY_PATH})
target_link_libraries(Win ${GLEW})