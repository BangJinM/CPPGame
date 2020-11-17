
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

project(Editor)

SET( EditorCPP
    main.cpp
    MainWindow.cpp
    MainWindow.h
    MainWindow.ui

    FileView.cpp
    FileView.h
    FileView.ui

    OutputView.cpp
    OutputView.h
    OutputView.ui

    EditorView.cpp
    EditorView.h
    EditorView.ui

    RuningView.cpp
    RuningView.h
    RuningView.ui

    PropertiesView.cpp
    PropertiesView.h
    PropertiesView.ui

    StructureView.cpp
    StructureView.h
    StructureView.ui

    OpenGLWidget.cpp
    OpenGLWidget.h
)

if(ANDROID)
  add_library(Editor SHARED
    ${EditorCPP}
  )
else()
  add_executable(Editor
    ${EditorCPP}
  )
endif()

find_package(Qt5 COMPONENTS Core Widgets Gui REQUIRED)
target_link_libraries(Editor PRIVATE Qt5::Widgets Qt5::Gui Qt5::Core)

find_package(glfw3 CONFIG REQUIRED)

target_link_libraries(Editor PRIVATE glfw )
