include(Scene/UI/CMakeLists.txt)

SET(FRAMEWORK_SCENE_HEADER 
Scene/Camera.h
Scene/ClassIDs.h
Scene/Component.h
Scene/GameObject.h
Scene/Light.h
Scene/Material.h
Scene/Mesh.h
Scene/MeshRenderer.h
Scene/Object.h
Scene/Renderer.h
Scene/Scene.h
Scene/SceneManager.h
Scene/Texture.h
Scene/Transform.h
)

SET(FRAMEWORK_SCENE_SRC 
Scene/Camera.cpp
Scene/GameObject.cpp
Scene/MeshRenderer.cpp
Scene/Renderer.cpp
Scene/Scene.cpp
Scene/SceneManager.cpp
Scene/Transform.cpp
)

list(APPEND FRAMEWORK_HEADER ${FRAMEWORK_SCENE_HEADER})
list(APPEND FRAMEWORK_SRC ${FRAMEWORK_SCENE_SRC})