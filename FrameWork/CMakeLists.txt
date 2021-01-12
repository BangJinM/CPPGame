project (Framework)


set(FRAMEWORK_HEADER)
set(FRAMEWORK_SRC)

include(Common/CMakeLists.txt)
include(File/CMakeLists.txt)
include(Parser/CMakeLists.txt)
include(Interface/CMakeLists.txt)
include(Math/CMakeLists.txt)

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
