add_library(RHI
    MShader.cpp
)

find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

target_link_libraries(RHI PRIVATE glad::glad)
target_link_libraries(RHI PRIVATE glfw )
