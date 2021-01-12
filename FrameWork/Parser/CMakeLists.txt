SET(FRAMEWORK_PARSER_HEADER 
Parser/MaterialParser.h
Parser/ObjParser.h
Parser/SceneParser.h
Parser/TextureParser.h
Parser/stb_image.h
Parser/TextureParser.h
Parser/ParserManager.h
Parser/IParser.h
)

SET(FRAMEWORK_PARSER_SRC 
Parser/ObjLoader.cpp
Parser/ParserManager.cpp
)

list(APPEND FRAMEWORK_HEADER ${FRAMEWORK_PARSER_HEADER})
list(APPEND FRAMEWORK_SRC ${FRAMEWORK_PARSER_SRC})