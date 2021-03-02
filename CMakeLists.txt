cmake_minimum_required (VERSION 3.1) 
set (CMAKE_C_STANDARD 11)
set (CMAKE_CXX_STANDARD 11)

# 设置VCPKG_ROOT所在的位置
set(VCPKG_TARGET_TRIPLET x86-windows)
set(VCPKG_ROOT "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")
set(CMAKE_TOOLCHAIN_FILE ${VCPKG_ROOT} CACHE STRING "")

project (GameEngine)

include_directories("${PROJECT_SOURCE_DIR}/FrameWork/Common")
include_directories("${PROJECT_SOURCE_DIR}/FrameWork/Parser")
include_directories("${PROJECT_SOURCE_DIR}/FrameWork/Interface")
include_directories("${PROJECT_SOURCE_DIR}/FrameWork/File")
include_directories("${PROJECT_SOURCE_DIR}/FrameWork/Math")
include_directories("${PROJECT_SOURCE_DIR}/FrameWork/Logger")
include_directories("${PROJECT_SOURCE_DIR}/FrameWork/Memory")
include_directories("${PROJECT_SOURCE_DIR}/FrameWork/Scene")
include_directories("${PROJECT_SOURCE_DIR}/FrameWork")


add_subdirectory(GameLogic)
add_subdirectory(FrameWork)




