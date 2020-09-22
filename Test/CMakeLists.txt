add_executable(TextRenderer TextRenderer.cpp)
target_link_libraries(TextRenderer Common)

find_library(GLEW glfw3 PATHS ${MYGE_EXTERNAL_LIBRARY_PATH})
target_link_libraries(TextRenderer ${GLEW})

find_library(FREETYPE freetype PATHS ${MYGE_EXTERNAL_LIBRARY_PATH})
target_link_libraries(TextRenderer ${FREETYPE})
#
#add_executable(InputManagerTest InputManagerTest.cpp)
#target_link_libraries(InputManagerTest Common)
#
#add_executable(Material MaterialTest.cpp)
#target_link_libraries(Material Common)