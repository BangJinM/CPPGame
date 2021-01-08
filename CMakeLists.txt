cmake_minimum_required (VERSION 3.1) 
set (CMAKE_C_STANDARD 11)
set (CMAKE_CXX_STANDARD 11)

# 设置VCPKG_ROOT所在的位置
set(VCPKG_TARGET_TRIPLET x86-windows)
set(VCPKG_ROOT "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")
set(CMAKE_TOOLCHAIN_FILE ${VCPKG_ROOT} CACHE STRING "")

set(GAMEENGINE_RHI_OPENGL true)

project (GameEngine)

include_directories("${PROJECT_SOURCE_DIR}/FrameWork/Common")
include_directories("${PROJECT_SOURCE_DIR}/FrameWork/Common/Scene")
include_directories("${PROJECT_SOURCE_DIR}/FrameWork/Common/Parser")
include_directories("${PROJECT_SOURCE_DIR}/FrameWork/Common/3dloader")
include_directories("${PROJECT_SOURCE_DIR}/FrameWork/Interface")
include_directories("${PROJECT_SOURCE_DIR}/FrameWork/Math")

if(GAMEENGINE_RHI_OPENGL)
    include_directories("${PROJECT_SOURCE_DIR}/RHI/OpenGL")
    add_subdirectory(RHI/OpenGL)
    add_subdirectory(Platform)
else(GAMEENGINE_RHI_QT_OPENGL)
    include_directories("${PROJECT_SOURCE_DIR}/RHI/QtOpenGL")
    add_subdirectory(RHI/QtOpenGL)
    add_subdirectory(Editor)
endif()


add_subdirectory(FrameWork)




