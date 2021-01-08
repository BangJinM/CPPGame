include(Common/UI/CMakeLists.txt)
include(Common/3dloader/CMakeLists.txt)
include(Common/Parser/CMakeLists.txt)
include(Common/Scene/CMakeLists.txt)

SET(FRAMEWORK_COMMON_HEADER 
${FRAMEWORK_COMMON_3DLOADER_HEADER}
${FRAMEWORK_COMMON_PARSER_HEADER}
${FRAMEWORK_COMMON_SCENE_HEADER}
${FRAMEWORK_COMMON_UI_HEADER}
Common/Allocator.h
Common/AssetLoader.h
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
)

SET(FRAMEWORK_COMMON_SRC 
${FRAMEWORK_COMMON_3DLOADER_SRC}
${FRAMEWORK_COMMON_PARSER_SRC}
${FRAMEWORK_COMMON_SCENE_SRC}
${FRAMEWORK_COMMON_UI_SRC}
Common/InputManager.cpp
Common/BaseApplication.cpp
Common/Allocator.cpp
Common/MemoryManager.cpp
Common/AssetLoader.cpp
Common/BaseGraphicsManager.cpp
Common/AssetManager.cpp
)



