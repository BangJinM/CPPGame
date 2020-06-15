SET( Scene
    Scene/Material.cpp
    Scene/GameObject.cpp
    Scene/Mesh.cpp
    Scene/Scene.cpp
    Scene/MeshRendererCommand.cpp
    Scene/Material.cpp
)

SET( Parser
    Parser/ObjLoader.cpp
    Parser/ObjMaterialLoader.cpp
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
    ${Parser}
    ${CURRENT_HEADERS}
)
target_link_libraries(Common Glad)
add_library( Glad
    ${PROJECT_SOURCE_DIR}/External/src/glad/src/glad.c
)
target_include_directories(Glad PRIVATE "${PROJECT_SOURCE_DIR}/External/src/glad/include")

SOURCE_GROUP( src\\Parser FILES ${Parser})
SOURCE_GROUP( src\\Scene FILES ${Scene})
SOURCE_GROUP( src FILES ${Common})

