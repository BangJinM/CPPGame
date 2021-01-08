project (Framework)

include(Common/CMakeLists.txt)
include(File/CMakeLists.txt)

# aux_source_directory(. DIR_SRCS)

set(FRAMEWORK_HEADER 
    ${FRAMEWORK_FILE_HEADER}
    ${FRAMEWORK_COMMON_HEADER}
)

set(FRAMEWORK_SRC 
    ${FRAMEWORK_FILE_SRC}
    ${FRAMEWORK_COMMON_SRC}
)

list(APPEND FRAMEWORK_SRC ${FRAMEWORK_HEADER})

add_library(Framework ${FRAMEWORK_SRC})

find_package(glm CONFIG REQUIRED)
target_link_libraries(Framework PRIVATE glm)

find_package(cjson CONFIG REQUIRED)
target_link_libraries(Framework PRIVATE cjson)


if(GAMEENGINE_RHI_QT_OPENGL)
    find_package(Qt5 COMPONENTS Gui REQUIRED)
    target_link_libraries(Framework PRIVATE Qt5::Gui)
endif()

target_link_libraries(Framework PRIVATE RHI)
