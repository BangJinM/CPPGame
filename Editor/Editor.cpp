#include <iostream>
#include <string>

#include "AssetLoader.h"
#include "MemoryManager.h"
#include "cJSON.h"
#include "ObjLoader.h"
using namespace std;
using namespace GameEngine;

namespace GameEngine
{
	MemoryManager *g_pMemoryManager = new MemoryManager();
	AssetLoader *g_pAssetLoader = static_cast<AssetLoader *>(new AssetLoader);
} // namespace GameEngine

int main(int, char **)
{
	g_pMemoryManager->Initialize();
	g_pAssetLoader->Initialize();

	//std::string sv = "Shaders/default.vert";
	//std::string sf = "Shaders/default.frag";
	std::string name = "default";

	//float color[3] = {1, 1, 1};
	//std::string type = "Mat4";
	//std::string colorName = "color";
	///*cJSON * root = cJSON_CreateString(g_pAssetLoader->GetFileName(path).c_str());*/
	//cJSON *root = cJSON_CreateObject();
	//cJSON *object1 = cJSON_CreateObject();
	//cJSON_AddItemToObject(root, name.c_str(), object1);
	//cJSON_AddItemToObject(object1, "vert", cJSON_CreateString(sv.c_str()));
	//cJSON_AddItemToObject(object1, "frag", cJSON_CreateString(sf.c_str()));
	//cJSON *attrs = cJSON_CreateObject();
	//cJSON *attr = cJSON_CreateObject();
	//cJSON_AddItemToObject(object1, colorName.c_str(), attrs);
	//cJSON_AddItemToObject(attrs, colorName.c_str(), attr);
	//cJSON_AddItemToObject(attr, "name", cJSON_CreateString(colorName.c_str()));
	//cJSON_AddItemToObject(attr, "type", cJSON_CreateString(type.c_str()));
	//cJSON_AddItemToObject(attr, "value", cJSON_CreateFloatArray(color, 3));

	//char *cjson_str = cJSON_Print(root);
	//std::string fullPath = "../../Asset/Materials/" + name + ".gemtl";
	//g_pAssetLoader->WriteFile(cjson_str, fullPath);

	auto text = g_pAssetLoader->SyncOpenAndReadTextFileToString(("Materials/" + name + ".gemtl").c_str());
	auto json = cJSON_Parse(text.c_str());
	char *cjson_str = cJSON_Print(json);
	printf(cjson_str);
	g_pMemoryManager->Finalize();
	g_pAssetLoader->Finalize();
	delete g_pMemoryManager;
	delete g_pAssetLoader;
	return 0;
}
