cmake_minimum_required (VERSION 3.1) 
set (CMAKE_C_STANDARD 11)
set (CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# set (CMAKE_C_COMPILER               "clang-cl")
# set (CMAKE_C_FLAGS                  "-Wall")
# set (CMAKE_C_FLAGS_DEBUG            "/Debug")
# set (CMAKE_C_FLAGS_MINSIZEREL       "-Os -DNDEBUG")
# set (CMAKE_C_FLAGS_RELEASE          "-O4 -DNDEBUG")
# set (CMAKE_C_FLAGS_RELWITHDEBINFO   "-O2 /Debug")
# set (CMAKE_C_STANDARD 11)

# 设置VCPKG_ROOT所在的位置

set(VCPKG_TARGET_TRIPLET qt-x86-windows-static )
set(VCPKG_ROOT "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")
set(CMAKE_TOOLCHAIN_FILE ${VCPKG_ROOT} CACHE STRING "")

project (GameEngine)

include_directories("${PROJECT_SOURCE_DIR}/FrameWork/Common")
include_directories("${PROJECT_SOURCE_DIR}/FrameWork/Common/Scene")
include_directories("${PROJECT_SOURCE_DIR}/FrameWork/Common/Parser")
include_directories("${PROJECT_SOURCE_DIR}/FrameWork/Common/3dloader")
include_directories("${PROJECT_SOURCE_DIR}/FrameWork/Interface")
include_directories("${PROJECT_SOURCE_DIR}/FrameWork/Math")

add_subdirectory(FrameWork)
add_subdirectory(Platform)
add_subdirectory(Test)
add_subdirectory(Editor)

