//
// Copyright 2012-2015, Syoyo Fujita.
//
// Licensed under 2-clause BSD license.
//
//https://github.com/syoyo/tinyobjloader
#ifndef _GameEngine_Common_Scene_Parser_H
#define _GameEngine_Common_Scene_Parser_H

#include <string>
#include <vector>
#include <map>

#include "AssetLoader.h"
#include "ObjParser.h"
#include "MaterialParser.h"
#include "GameObject.h"
#include "cJSON.h"

namespace GameEngine
{
	extern AssetLoader *g_pAssetLoader;
	class SceneParser
	{

	public:
		static void Parse(std::string scenePath, Scene *scene)
		{
			std::string sceneStr = g_pAssetLoader->SyncOpenAndReadTextFileToString(scenePath.c_str());
			auto json = cJSON_Parse(sceneStr.c_str());
			int i = 0;
			for (; i < cJSON_GetArraySize(json); i++) //遍历最外层json键值对
			{
				cJSON *item = cJSON_GetArrayItem(json, i);
				if (cJSON_Object == item->type) //如果对应键的值仍为cJSON_Object就递归调用printJson
					parser(item, scene->gameObject);
			}
			delete json;
		}
		static bool strCompare(const char *str1, const char *str2)
		{
			std::string str = str1;
			return str.compare(str2) == 0;
		}

		static void parser(cJSON *root, GameObject *gb) //以递归的方式打印json的最内层键值对
		{
			int i = 0;
			GameObject *child = new GameObject();
			child->setName(root->string);
			for (; i < cJSON_GetArraySize(root); i++) //遍历最外层json键值对
			{
				cJSON *item = cJSON_GetArrayItem(root, i);

				
				
				if (cJSON_Object == item->type) //如果对应键的值仍为cJSON_Object就递归调用printJson
					parser(item, child);
				else //值不为json对象就直接打印出键和值
				{
					printf("%s->", item->string);
					printf("%s\n", cJSON_Print(item));
					if (strCompare(item->string, "mesh"))
					{
						ObjParser::Parse(item->valuestring, child);
					}
					else if (strCompare(item->string, "scale") || strCompare(item->string, "position"))
					{
						auto transform = child->getComponent<Transform>();
						if (transform == nullptr)
						{
							child->addComponent(Transform());
							transform = child->getComponent<Transform>();
						}
						if (strCompare(item->string, "scale"))
							transform->setScale(vecterFloat3(0, 0, 0));
						else if (strCompare(item->string, "position"))
						{
							transform->setPosition(vecterFloat3(0, 0, 0));
						}
					}
					else if (strCompare(item->string, "materials"))
					{
						int iSize = cJSON_GetArraySize(item);
						for (size_t mID = 0; mID < iSize; mID++)
						{
							Material* material = new Material();
							MaterialParser::Parse(cJSON_GetArrayItem(item, mID)->valuestring, material);
						}
					}
					
				}
			}
			printf("\n\n\n\n\n\n\n\n");
			gb->addChild(child);
		}
	}; // namespace GameEngine

} // namespace GameEngine

#endif // _TINY_OBJ_LOADER_H
