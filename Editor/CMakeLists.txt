include_directories("${PROJECT_SOURCE_DIR}/Editor")

SET( Editor
    Editor.cpp
)

add_executable(Editor Editor.cpp)
target_link_libraries(Editor Common cJson)