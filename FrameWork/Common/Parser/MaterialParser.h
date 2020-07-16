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
			for (; i < cJSON_GetArraySize(json); i++) //遍历最外层json键值对
			{
				cJSON *item = cJSON_GetArrayItem(json, i);
				//if (cJSON_Object == item->type) //如果对应键的值仍为cJSON_Object就递归调用printJson
				//	parser(item, scene->gameObject);
			}
			delete json;
        }
    }; // namespace GameEngine

} // namespace GameEngine

#endif // _TINY_OBJ_LOADER_H
