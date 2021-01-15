include(Common/UI/CMakeLists.txt)
include(Common/Scene/CMakeLists.txt)

SET(FRAMEWORK_COMMON_HEADER 
Common/Allocator.h
Common/AssetManager.h
Common/BaseApplication.h
Common/BaseGraphicsManager.h
Common/Buffer.h
Common/CommonIniter.h
Common/Config.h
Common/GfxConfiguration.h
Common/GfxConfiguration.h
Common/InputManager.h
Common/MemoryManager.h
Common/ShaderBase.h
Common/ShaderManager.h
)

SET(FRAMEWORK_COMMON_SRC 
Common/InputManager.cpp
Common/BaseApplication.cpp
Common/Allocator.cpp
Common/MemoryManager.cpp
Common/BaseGraphicsManager.cpp
Common/AssetManager.cpp
)

list(APPEND FRAMEWORK_HEADER ${FRAMEWORK_COMMON_HEADER})
list(APPEND FRAMEWORK_SRC ${FRAMEWORK_COMMON_SRC})


