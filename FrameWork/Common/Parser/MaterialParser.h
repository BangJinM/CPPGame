//
// Copyright 2012-2015, Syoyo Fujita.
//
// Licensed under 2-clause BSD license.
//
//https://github.com/syoyo/tinyobjloader
#ifndef _GameEngine_Common_Material_Parser_H
#define _GameEngine_Common_Material_Parser_H

#include <string>
#include <vector>
#include <map>

#include "cJSON.h"
#include "Material.h"

namespace GameEngine
{
    extern AssetLoader *g_pAssetLoader;
    class MaterialParser
    {

    public:
        static void Parse(std::string scenePath, Material *material)
        {
            std::string sceneStr = g_pAssetLoader->SyncOpenAndReadTextFileToString(scenePath.c_str());
            auto json = cJSON_Parse(sceneStr.c_str());
			int i = 0;
			auto frag = cJSON_GetObjectItem(json, "frag");
			auto vert = cJSON_GetObjectItem(json, "vert");
			std::string vertStr = g_pAssetLoader->SyncOpenAndReadTextFileToString(vert->valuestring);
			std::string fragStr = g_pAssetLoader->SyncOpenAndReadTextFileToString(frag->valuestring);
			Shader* shader = new Shader(vertStr, fragStr);
			material->setShader(shader);
            
			auto paramsNode = cJSON_GetObjectItem(json, "params");
			if (paramsNode) {
				auto count = cJSON_GetArraySize(paramsNode);
				for (size_t i = 0; i < count; i++)
				{
					cJSON *item = cJSON_GetArrayItem(paramsNode, i);
                    std::string name = item->string;
					std::string type = cJSON_GetObjectItem(item, "type")->valuestring;
					if (type.compare("texture") == 0) {
						std::string pathStr = cJSON_GetObjectItem(item, "path")->valuestring;
                        material->AddProperty(pathStr.c_str(), name, pathStr.size(), MaterialType::Texture);
					}
					else if (type.compare("vec4") == 0) {

					}
				}
			}
			delete json;
        }
    }; // namespace GameEngine

} // namespace GameEngine

#endif // _TINY_OBJ_LOADER_H