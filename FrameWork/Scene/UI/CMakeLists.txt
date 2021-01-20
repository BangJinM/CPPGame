SET(FRAMEWORK_SCENE_UI_HEADER 
Scene/UI/Button.h
Scene/UI/CanvasRenderer.h
Scene/UI/Font.h
Scene/UI/Image.h
Scene/UI/Label.h
Scene/UI/Widget.h
)

SET(FRAMEWORK_SCENE_UI_SRC 
Scene/UI/Button.cpp
Scene/UI/CanvasRenderer.cpp
Scene/UI/Font.cpp
Scene/UI/Image.cpp
Scene/UI/Label.cpp
Scene/UI/Widget.cpp
)

list(APPEND FRAMEWORK_HEADER ${FRAMEWORK_SCENE_UI_HEADER})
list(APPEND FRAMEWORK_SRC ${FRAMEWORK_SCENE_UI_SRC})