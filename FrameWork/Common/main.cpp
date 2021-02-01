#include "AssetLoader.h"
#include "AssetManager.h"
#include "BaseApplication.h"
#include "BaseGraphicsManager.h"
#include "GameLogic.h"
#include "InputManager.h"
#include "MemoryManager.h"
#include "ParserManager.h"
#include "SceneManager.h"
#include "ShaderManager.h"
#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP
using namespace GameEngine;

namespace GameEngine
{
    extern BaseApplication *g_pApp;
    extern MemoryManager *g_pMemoryManager;
    extern InputManager *g_pInputManager;
    extern AssetLoader *g_pAssetLoader;
    extern BaseGraphicsManager *g_pGraphicsManager;
    extern AssetManager *g_pAssetManager;
    extern ParserManager *g_pParserManager;
    extern ShaderManager *g_pShaderManager;
    extern GameLogic *g_pGameLogic;
    extern SceneManager *g_pSceneManager;

}  // namespace GameEngine

int main(int argc, char *argv[])
{
    el::Loggers::getLogger("logger")->info("GameEngine Begin...");

    for (int i = 0; i < argc; i++)
        el::Loggers::getLogger("logger")->info(argv[i]);

    int ret;
    vector<IRuntimeModule *> run_time_modules;
    run_time_modules.push_back(g_pApp);
    run_time_modules.push_back(g_pMemoryManager);
    run_time_modules.push_back(g_pParserManager);
    run_time_modules.push_back(g_pInputManager);
    run_time_modules.push_back(g_pAssetLoader);
    run_time_modules.push_back(g_pAssetManager);
    run_time_modules.push_back(g_pGraphicsManager);
    run_time_modules.push_back(g_pShaderManager);
    run_time_modules.push_back(g_pSceneManager);
    run_time_modules.push_back(g_pGameLogic);

    for (auto &module : run_time_modules)
    {
        if ((ret = module->Initialize()) != 0)
        {
            el::Loggers::getLogger("logger")->error(
                "nitialize failed, will exit now.");
            return ret;
        }
    }

    int i = 1;
    while (!g_pApp->IsQuit())
    {
        for (auto &module : run_time_modules)
        {
            module->Tick();
        }
    }

    for (auto &module : run_time_modules)
    {
        module->Finalize();
    }

    for (vector<IRuntimeModule *>::const_iterator itr =
             run_time_modules.begin();
         itr != run_time_modules.end(); ++itr)
    {
        delete *itr;
    }
    run_time_modules.clear();

    el::Loggers::getLogger("logger")->info("GameEngine End...");
    return 0;
}
