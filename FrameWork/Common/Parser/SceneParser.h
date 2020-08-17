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
#include "MeshRenderer.h"
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
		static std::shared_ptr<Object> compareGameObject(cJSON *root)
		{
			std::shared_ptr<GameObject> gameobject = std::make_shared<GameObject>();
			auto paramsNode = cJSON_GetObjectItem(root, "name");
			if (paramsNode)
			{
				gameobject->setName(paramsNode->string);
			}
			return gameobject;
		}

		static std::shared_ptr<Object> compareTransform(cJSON *root)
		{
			std::shared_ptr<Transform> gameobject = std::make_shared<Transform>();
			auto paramsNode = cJSON_GetObjectItem(root, "scale");
			if (paramsNode)
			{
				vecterFloat3 vec3(vecterFloat3(cJSON_GetArrayItem(paramsNode, 0)->valuedouble, cJSON_GetArrayItem(paramsNode, 1)->valuedouble, cJSON_GetArrayItem(paramsNode, 2)->valuedouble));
				gameobject->setScale(vec3);
			}
			paramsNode = cJSON_GetObjectItem(root, "position");
			if (paramsNode)
			{
				vecterFloat3 vec3(vecterFloat3(cJSON_GetArrayItem(paramsNode, 0)->valuedouble, cJSON_GetArrayItem(paramsNode, 1)->valuedouble, cJSON_GetArrayItem(paramsNode, 2)->valuedouble));
				gameobject->setPosition(vec3);
			}
			paramsNode = cJSON_GetObjectItem(root, "rotation");
			if (paramsNode)
			{
				vecterFloat3 vec3(vecterFloat3(cJSON_GetArrayItem(paramsNode, 0)->valuedouble, cJSON_GetArrayItem(paramsNode, 1)->valuedouble, cJSON_GetArrayItem(paramsNode, 2)->valuedouble));
				gameobject->setPosition(vec3);
			}
			return gameobject;
		}

		static std::shared_ptr<Object> compareCamera(cJSON *root)
		{
			std::shared_ptr<Camera> gameobject = std::make_shared<Camera>();
			return gameobject;
		}

		static std::shared_ptr<Object> compareMeshRenderer(cJSON *root)
		{
			std::shared_ptr<MeshRenderer> gameobject = std::make_shared<MeshRenderer>();
			return gameobject;
		}

		static bool strCompare(const char *str1, const char *str2)
		{

			std::string str = str1;
			return str.compare(str2) == 0;
		}

		static std::shared_ptr<Object> parser(cJSON *root, std::shared_ptr<GameObject> gb) //以递归的方式打印json的最内层键值对
		{
			static const struct
			{
				const char * name;
				std::function<std::shared_ptr<Object>(cJSON *root)> func;
			} attribute_locations[] =
				{
					{"GameObject", compareGameObject},
					{"Transform", compareTransform},
					{"MeshRenderer", compareMeshRenderer},
					{"Camera", compareCamera}};
			const int size = sizeof(attribute_locations) / sizeof(attribute_locations[0]);
			int i = 0;
			std::shared_ptr<Object> object;
			auto type = root->string;

			for (size_t i = 0; i < size; i++)
			{
				if(strCompare(type, attribute_locations[i].name)){
					object = attribute_locations[i].func(root);
				}
			}

			auto paramsNode = cJSON_GetObjectItem(root, "fileID");
			if (paramsNode && object)
			{
				object->SetFileID(paramsNode->valueint);
			}
			return object;
		}

	}; // namespace GameEngine

} // namespace GameEngine

#endif // _TINY_OBJ_LOADER_H
