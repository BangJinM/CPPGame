//
// Copyright 2012-2015, Syoyo Fujita.
//
// Licensed under 2-clause BSD license.
//
//https://github.com/syoyo/tinyobjloader
#pragma once

#include <string>
#include <vector>
#include <map>

#include "Config.h"
#include "cjson/cJSON.h"
#include "Material.h"
#include "Shader.h"
#include "IParser.h"
#include "AssetLoader.h"
#include "ShaderManager.h"
GameEngineBegin extern GameEngineFile::AssetLoader *g_pAssetLoader;
extern ShaderManager *g_pShaderManager;
GameEngineEnd
	UseGameEngine
		GameEngineParserBegin

	class MaterialParser : public IParser
{

public:
	virtual SharedObject Parser(const std::string path) override
	{
		SharedMaterial material = std::make_shared<Material>();
		std::string mstr = g_pAssetLoader->SyncOpenAndReadTextFileToString(path.c_str());
		auto json = cJSON_Parse(mstr.c_str());
		int i = 0;
		auto frag = cJSON_GetObjectItem(json, "frag");
		auto vert = cJSON_GetObjectItem(json, "vert");

		std::string vertStr = g_pAssetLoader->SyncOpenAndReadTextFileToString(vert->valuestring);
		std::string fragStr = g_pAssetLoader->SyncOpenAndReadTextFileToString(frag->valuestring);

		material->shaderID = g_pShaderManager->AddShaderByPath(vertStr, fragStr);

		auto paramsNode = cJSON_GetObjectItem(json, "params");
		if (paramsNode)
		{
			auto count = cJSON_GetArraySize(paramsNode);
			for (size_t i = 0; i < count; i++)
			{
				cJSON *item = cJSON_GetArrayItem(paramsNode, i);
				std::string name = item->string;
				std::string type = cJSON_GetObjectItem(item, "type")->valuestring;
				if (type.compare("texture") == 0)
				{
					std::string pathStr = cJSON_GetObjectItem(item, "path")->valuestring;
					material->AddProperty(pathStr.c_str(), name, pathStr.size(), MaterialType::T_Texture);
				}
				else if (type.compare("vec4") == 0)
				{
				}
			}
		}
		delete json;
		return material;
	}
}; // namespace GameEngine
GameEngineParserEnd
