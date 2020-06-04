#include <iostream>
#include <string>
#include "AssetLoader.h"
#include "MemoryManager.h"
#include "ObjParser.h"
#include "Scene.h"

using namespace std;
using namespace GameEngine;

namespace GameEngine {
    MemoryManager* g_pMemoryManager = new MemoryManager();
}

int main(int , char** )
{
    g_pMemoryManager->Initialize();

    AssetLoader asset_loader;
    string shader_pgm = asset_loader.SyncOpenAndReadTextFileToString("Scene/Shape_Cube.obj");
    cout << shader_pgm;

    g_pMemoryManager->Finalize();

    delete g_pMemoryManager;

    return 0;
}

