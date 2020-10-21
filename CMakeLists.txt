cmake_minimum_required (VERSION 3.1) 
set (CMAKE_C_STANDARD 11)
set (CMAKE_CXX_STANDARD 11)

# set (CMAKE_C_COMPILER               "clang-cl")
# set (CMAKE_C_FLAGS                  "-Wall")
# set (CMAKE_C_FLAGS_DEBUG            "/Debug")
# set (CMAKE_C_FLAGS_MINSIZEREL       "-Os -DNDEBUG")
# set (CMAKE_C_FLAGS_RELEASE          "-O4 -DNDEBUG")
# set (CMAKE_C_FLAGS_RELWITHDEBINFO   "-O2 /Debug")
# set (CMAKE_C_STANDARD 11)

project (GameEngine)

include_directories("${PROJECT_SOURCE_DIR}/FrameWork/Common")
include_directories("${PROJECT_SOURCE_DIR}/FrameWork/Common/Scene")
include_directories("${PROJECT_SOURCE_DIR}/FrameWork/Common/Parser")
include_directories("${PROJECT_SOURCE_DIR}/FrameWork/Common/3dloader")
include_directories("${PROJECT_SOURCE_DIR}/FrameWork/Interface")
include_directories("${PROJECT_SOURCE_DIR}/FrameWork/Math")


set(MYGE_TARGET_PLATFORM "Windows")

set(MYGE_EXTERNAL_ROOT ${PROJECT_SOURCE_DIR}/External/${MYGE_TARGET_PLATFORM}/)

include_directories("${PROJECT_SOURCE_DIR}/Platform/${MYGE_TARGET_PLATFORM}")
include_directories("${PROJECT_SOURCE_DIR}/External/src/glm")
include_directories("${PROJECT_SOURCE_DIR}/External/src/glad/include")
include_directories("${PROJECT_SOURCE_DIR}/External/src/cJSON")
include_directories("${PROJECT_SOURCE_DIR}/External/src/freetype/include")

add_library( cJson
    ${PROJECT_SOURCE_DIR}/External/src/cJson/cJson.c
)

add_library( Glad
    ${PROJECT_SOURCE_DIR}/External/src/glad/src/glad.c
)

include_directories("${MYGE_EXTERNAL_ROOT}include")
set(MYGE_EXTERNAL_LIBRARY_PATH ${MYGE_EXTERNAL_ROOT}lib/)

add_subdirectory(FrameWork)
add_subdirectory(Platform)
add_subdirectory(Test)
# add_subdirectory(Editor)

