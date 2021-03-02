SET(FRAMEWORK_PARSER_HEADER 
Scene/Parser/MaterialParser.h
Scene/Parser/ObjParser.h
Scene/Parser/stb_image.h
Scene/Parser/TextureParser.h
Scene/Parser/ParserManager.h
Scene/Parser/IParser.h
)

SET(FRAMEWORK_PARSER_SRC 
Scene/Parser/ObjLoader.cpp
Scene/Parser/ParserManager.cpp
)

list(APPEND FRAMEWORK_HEADER ${FRAMEWORK_PARSER_HEADER})
list(APPEND FRAMEWORK_SRC ${FRAMEWORK_PARSER_SRC})