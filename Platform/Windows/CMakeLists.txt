add_executable(Windows 
    GraphicsManager.cpp
    GamePlatform-opengl.cpp
    InputManagerWindows.cpp
)
target_link_libraries(Windows Common)

if(WIN32)
    find_library(GLFW3 glfw3 PATHS ${MYGE_EXTERNAL_LIBRARY_PATH})
else()
    find_library(GLFW3 glfw3 PATHS ${MYGE_EXTERNAL_LIBRARY_PATH})
endif(WIN32)

target_link_libraries(Windows ${GLFW3})




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
