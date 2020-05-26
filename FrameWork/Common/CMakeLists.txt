SET( Scene
    Scene/Material.cpp
)

SET( Common
    InputManager.cpp
    BaseApplication.cpp
    Allocator.cpp
    MemoryManager.cpp
    AssetLoader.cpp
    main.cpp
)

add_library(Common
    ${Common}    
    ${Scene}
)

SOURCE_GROUP( Common\\Scene FILES ${Scene})
SOURCE_GROUP( Common FILES ${Common})