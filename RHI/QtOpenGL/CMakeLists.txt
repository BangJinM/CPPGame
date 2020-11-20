
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

project(RHI)

add_library(RHI
    MShader.cpp
)

find_package(Qt5 COMPONENTS Gui REQUIRED)
target_link_libraries(RHI PRIVATE Qt5::Gui)
