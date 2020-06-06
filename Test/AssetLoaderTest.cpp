#include <iostream>
#include <string>
#include "AssetLoader.h"
#include "MemoryManager.h"
#include "ObjParser.h"
#include "Scene.h"
#include "ObjParser.h"
#include "AssetLoader.h"
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

	std::vector<shape_t> shapes;
	std::vector<material_t> materials;
	LoadObj(shapes, materials, "Scene/53b2ae21a87d7.obj", "Scene/");
    g_pMemoryManager->Finalize();

    delete g_pMemoryManager;

    return 0;
}
