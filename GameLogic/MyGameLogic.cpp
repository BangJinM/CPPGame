#include "MyGameLogic.h"

#include "AssetLoader.h"
#include "Camera.h"
#include "Scene.h"
#include "SceneManager.h"

namespace GameEngine
{
    extern SceneManager *g_pSceneManager;
    extern AssetLoader *g_pAssetLoader;
    int MyGameLogic::Initialize()
    {
        std::string sceneStr = g_pAssetLoader->SyncOpenAndReadTextFileToString("Scene/new.scene");
        auto json = cJSON_Parse(sceneStr.c_str());
        SharePtr<Scene> m_Scene = std::make_shared<Scene>();
        m_Scene->OnDeserialize(json);
        g_pSceneManager->SetNextScene(m_Scene);
        return 0;
    }
    void MyGameLogic::Finalize() {}
    void MyGameLogic::Tick(float deltaTime) {}

}  // namespace GameEngine
