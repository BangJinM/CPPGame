project (Windows)
add_executable(Windows 
    GraphicsManager.cpp
    GamePlatform-opengl.cpp
    InputManagerWindows.cpp
)

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)

target_link_libraries(Windows PRIVATE glfw )
target_link_libraries(Windows PRIVATE glad::glad)
target_link_libraries(Windows PRIVATE Common )




#find_package(OpenGL REQUIRED)

#add_library(WindowsApplication WindowsApplication.cpp)



# ---------------------------------------------------------



#add_executable(Windows2 
#    OpenGLApplication.cpp
#    ${PROJECT_SOURCE_DIR}/External/src/glad/src/glad_wgl.c
#)
#target_link_libraries(Windows2 Common WindowsApplication ${OPENGL_LIBRARIES})
#
#target_include_directories(Windows2 PRIVATE "${PROJECT_SOURCE_DIR}/External/src/glad/include")
