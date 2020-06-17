#include <iostream>
#include <string>
#include "AssetLoader.h"
#include "MemoryManager.h"
#include "Scene.h"
#include "AssetLoader.h"
#include "ObjLoader.h"
#include "ObjMaterialLoader.h"
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
	std::vector<shape_t> shapes;
	std::vector<material_t> materials;
	ObjParser parser;
	parser.Parse(g_pAssetLoader->SyncOpenAndReadTextFileToString("Scene/53b2ae21a87d7.obj"));
    g_pMemoryManager->Finalize();
    g_pAssetLoader->Finalize();
    delete g_pMemoryManager;
	delete g_pAssetLoader;
    return 0;
}
