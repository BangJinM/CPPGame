SET( Scene
    Scene/GameObject.cpp
    Scene/Scene.cpp
    Scene/Transform.cpp
    Scene/Camera.cpp
    Scene/Renderer.cpp
    Scene/MeshRenderer.cpp
    Scene/SceneManager.cpp
)

SET( UI
    UI/Button.cpp
    UI/CanvasRenderer.cpp
    UI/Image.cpp
    UI/Label.cpp
    UI/Widget.cpp
    UI/Font.cpp
)

#SET( Parser
#)

SET( 3dloader
    3dloader/ObjLoader.cpp
)

SET( Common
    InputManager.cpp
    BaseApplication.cpp
    Allocator.cpp
    MemoryManager.cpp
    AssetLoader.cpp
    BaseGraphicsManager.cpp
    AssetManager.cpp
    main.cpp
)

file(GLOB_RECURSE CURRENT_HEADERS  *.h *.hpp)
source_group(include FILES ${CURRENT_HEADERS}) 

add_library(Common
    ${Common}    
    ${Scene}
    ${UI}
    ${3dloader}
    ${CURRENT_HEADERS}
)
target_link_libraries(Common Glad cJson)

# find_library(FREETYPE freetype PATHS ${MYGE_EXTERNAL_LIBRARY_PATH})
# target_link_libraries(Common ${FREETYPE})

SOURCE_GROUP( src\\Parser FILES ${Parser})
SOURCE_GROUP( src\\3dloader FILES ${3dloader})
SOURCE_GROUP( src\\Scene FILES ${Scene})
SOURCE_GROUP( src\\UI FILES ${UI})
SOURCE_GROUP( src FILES ${Common})

