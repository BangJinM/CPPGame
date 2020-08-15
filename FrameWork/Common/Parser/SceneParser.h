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
#include "Light.h"
#include "cJSON.h"
#include "MyMath.h"
#include "AssetManager.h"

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

		static void parser(cJSON *root, std::shared_ptr< GameObject > gb) //以递归的方式打印json的最内层键值对
		{
			int i = 0;
			std::shared_ptr< GameObject > child = std::make_shared<GameObject>();
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
						child->m_Mesh= AssetManager::LoadMesh(item->valuestring);
					}
					else if (strCompare(item->string, "scale") || strCompare(item->string, "position") || strCompare(item->string, "rotation"))
					{
						auto transform = child->getComponent<Transform>();
						if (transform == nullptr)
						{
							child->addComponent(new Transform());
							transform = child->getComponent<Transform>();
						}
						vecterFloat3 vec3(vecterFloat3(cJSON_GetArrayItem(item, 0)->valuedouble, cJSON_GetArrayItem(item, 1)->valuedouble, cJSON_GetArrayItem(item, 2)->valuedouble));
						if (strCompare(item->string, "scale"))
							transform->setScale(vec3);
						else if (strCompare(item->string, "position"))
						{
							transform->setPosition(vec3);
						}
						else
						{
							transform->setRotation(vec3);
						}
					}
					else if (strCompare(item->string, "materials"))
					{
						int iSize = cJSON_GetArraySize(item);
						for (size_t mID = 0; mID < iSize; mID++)
						{
							child->m_Materials.push_back(AssetManager::LoadMaterial(cJSON_GetArrayItem(item, mID)->valuestring));
						}
					}
					else if (strCompare(item->string, "camera"))
					{
						auto camera = child->getComponent<Camera>();
						if (camera == nullptr)
						{
							child->addComponent(new Camera());
							camera = child->getComponent<Camera>();
						}
					}
					else if (strCompare(item->string, "light"))
					{
						auto light = child->getComponent<Light>();
						if (light == nullptr)
						{
							int type = cJSON_GetObjectItem(item, "type")->valueint;
							if (type == Light::LightType::DirectionalLight)
							{
								child->addComponent(new DirectionalLight());
								light = child->getComponent<Light>();
							}
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
