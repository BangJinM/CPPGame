

project(Editor LANGUAGES CXX)



# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

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

find_package(Qt5 COMPONENTS Widgets REQUIRED)
target_link_libraries(Editor PRIVATE Qt5::Widgets)
