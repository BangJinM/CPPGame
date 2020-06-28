SET( Scene
    Scene/GameObject.cpp
    Scene/Mesh.cpp
    Scene/Scene.cpp
    Scene/MeshRendererCommand.cpp
    Scene/Transform.cpp
    Scene/Camera.cpp
    Scene/Material.cpp
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
    GraphicsManager.cpp
    main.cpp
)

file(GLOB_RECURSE CURRENT_HEADERS  *.h *.hpp)
source_group(include FILES ${CURRENT_HEADERS}) 

add_library(Common
    ${Common}    
    ${Scene}
    #${Parser}
    ${3dloader}
    ${CURRENT_HEADERS}
)
target_link_libraries(Common Glad)
add_library( Glad
    ${PROJECT_SOURCE_DIR}/External/src/glad/src/glad.c
)
target_include_directories(Glad PRIVATE "${PROJECT_SOURCE_DIR}/External/src/glad/include")

SOURCE_GROUP( src\\Parser FILES ${Parser})
SOURCE_GROUP( src\\3dloader FILES ${3dloader})
SOURCE_GROUP( src\\Scene FILES ${Scene})
SOURCE_GROUP( src FILES ${Common})

