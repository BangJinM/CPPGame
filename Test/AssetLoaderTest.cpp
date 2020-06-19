#include <iostream>
#include <string>
#include "AssetLoader.h"
#include "MemoryManager.h"
#include "Scene.h"
#include "AssetLoader.h"
#include "ObjLoader.h"
#include "ObjParser.h"
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
    tinyobj::LoadObj(shapes, materials, "Scene/53b2ae21a87d7.obj", "Scene/");
	ObjParser parser;
	parser.Parse(shapes);
    g_pMemoryManager->Finalize();
    g_pAssetLoader->Finalize();
    delete g_pMemoryManager;
	delete g_pAssetLoader;
    return 0;
}
