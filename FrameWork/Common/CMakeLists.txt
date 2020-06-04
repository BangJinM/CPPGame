SET( Scene
    Scene/Material.cpp
)

SET( Parser
    Parser/ObjParser.cpp
)

SET( Common
    InputManager.cpp
    BaseApplication.cpp
    Allocator.cpp
    MemoryManager.cpp
    AssetLoader.cpp
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


SOURCE_GROUP( src\\Parser FILES ${Parser})
SOURCE_GROUP( src\\Scene FILES ${Scene})
SOURCE_GROUP( src FILES ${Common})

