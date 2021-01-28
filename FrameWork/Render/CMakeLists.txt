include(Render/Draw/CMakeLists.txt)
include(Render/Sub/CMakeLists.txt)

SET(FRAMEWORK_RENDER_HEADER 
Render/IDrawPass.h
Render/IPass.h
Render/ISubPass.h
)

SET(FRAMEWORK_RENDER_SRC 
)

list(APPEND FRAMEWORK_HEADER ${FRAMEWORK_RENDER_HEADER})
list(APPEND FRAMEWORK_SRC ${FRAMEWORK_RENDER_SRC})