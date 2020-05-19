cmake_minimum_required (VERSION 3.1) 
set (CMAKE_C_STANDARD 11)
set (CMAKE_CXX_STANDARD 11)

set (CMAKE_C_COMPILER               "clang-cl")
set (CMAKE_C_FLAGS                  "-Wall")
set (CMAKE_C_FLAGS_DEBUG            "/Debug")
set (CMAKE_C_FLAGS_MINSIZEREL       "-Os -DNDEBUG")
set (CMAKE_C_FLAGS_RELEASE          "-O4 -DNDEBUG")
set (CMAKE_C_FLAGS_RELWITHDEBINFO   "-O2 /Debug")
set (CMAKE_C_STANDARD 11)
set (CMAKE_CXX_COMPILER             "clang-cl")
set (CMAKE_CXX_FLAGS                "-Wall -Xclang -std=gnu++14")
set (CMAKE_CXX_FLAGS_DEBUG          "/Debug")
set (CMAKE_CXX_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
set (CMAKE_CXX_FLAGS_RELEASE        "-O4 -DNDEBUG")
set (CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 /Debug")

project (GameEngine)

include_directories("${PROJECT_SOURCE_DIR}/FrameWork/Common")
include_directories("${PROJECT_SOURCE_DIR}/FrameWork/Interface")


set(MYGE_TARGET_PLATFORM "Win")


set(MYGE_EXTERNAL_ROOT ${PROJECT_SOURCE_DIR}/External/${MYGE_TARGET_PLATFORM}/)

include_directories("${PROJECT_SOURCE_DIR}/Platform/${MYGE_TARGET_PLATFORM}")

include_directories("${MYGE_EXTERNAL_ROOT}include")
set(MYGE_EXTERNAL_LIBRARY_PATH ${MYGE_EXTERNAL_ROOT}lib/)

add_subdirectory(FrameWork)
add_subdirectory(Platform)

add_subdirectory(Test)
