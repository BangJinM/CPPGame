add_executable(Windows 
    GamePlatform-opengl.cpp
)
target_link_libraries(Windows Common)

find_library(GLFW3 libglfw3 PATHS ${MYGE_EXTERNAL_LIBRARY_PATH})
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