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

	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string path = "Scene/Shape_Cube.obj";
	tinyobj::LoadObj(shapes, materials, path.c_str(), "Materials/");

	/*cJSON * root = cJSON_CreateString(g_pAssetLoader->GetFileName(path).c_str());*/
	cJSON * root = cJSON_CreateObject();
	cJSON * object1 = cJSON_CreateObject();
	cJSON_AddItemToObject(root, g_pAssetLoader->GetFileName(path).c_str(), object1);
	for (size_t i = 0; i < shapes.size(); i++)
	{
		auto shap = shapes[i];
		cJSON * item = cJSON_CreateObject();
		cJSON_AddItemToObject(object1, shap.name.c_str(), item);
		if (shap.mesh.indices.size() > 0)
			cJSON_AddItemToObject(item, "indices", cJSON_CreateIntArray(&shap.mesh.indices[0], shap.mesh.indices.size()));
		if (shap.mesh.normals.size() > 0)
			cJSON_AddItemToObject(item, "normals", cJSON_CreateFloatArray(&shap.mesh.normals[0], shap.mesh.normals.size()));
		if (shap.mesh.texcoords.size() > 0)
			cJSON_AddItemToObject(item, "texcoords", cJSON_CreateFloatArray(&shap.mesh.texcoords[0], shap.mesh.texcoords.size()));
		if (shap.mesh.positions.size() > 0)
			cJSON_AddItemToObject(item, "positions", cJSON_CreateFloatArray(&shap.mesh.positions[0], shap.mesh.positions.size()));
	}
	char *cjson_str = cJSON_Print(root);
    auto fullPath = "../../Asset/" + path;
	g_pAssetLoader->WriteFile(cjson_str, fullPath);
	printf(cjson_str);
    g_pMemoryManager->Finalize();
    g_pAssetLoader->Finalize();
    delete g_pMemoryManager;
    delete g_pAssetLoader;
    return 0;
}
