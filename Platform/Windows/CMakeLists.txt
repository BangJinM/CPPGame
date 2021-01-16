set(WINDOWS_HEADER
    GamePlatform-opengl.h
    WindowsConfig.h
    InputManagerWindows.h
)
set(WINDOWS_SRC
    GamePlatform-opengl.cpp
    InputManagerWindows.cpp
)

add_library(Windows ${WINDOWS_SRC} ${WINDOWS_HEADER})

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)

target_link_libraries(Windows PRIVATE glfw )
target_link_libraries(Windows PRIVATE glad::glad)
target_link_libraries(Windows PRIVATE Framework )
target_link_libraries(Windows PRIVATE RHI )
