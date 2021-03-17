#include "MyGameLogic.h"

#include "MyMath.h"
#include "AssetLoader.h"
#include "Camera.h"
#include "GameObject.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Transform.h"
#include <glm/gtx/string_cast.hpp>
#include "easylogging++.h"

namespace GameEngine
{
    extern SceneManager *g_pSceneManager;
    extern AssetLoader *g_pAssetLoader;
    VecterFloat3 rotation(0);
    int MyGameLogic::Initialize()
    {
        std::string sceneStr = g_pAssetLoader->SyncOpenAndReadTextFileToString("Scene/new.scene");
        auto json = cJSON_Parse(sceneStr.c_str());
        m_Scene = std::make_shared<Scene>();
        m_Scene->OnDeserialize(json);
        g_pSceneManager->SetNextScene(m_Scene);

        return 0;
    }
    void MyGameLogic::Finalize() {}
    void MyGameLogic::Tick(float deltaTime)
    {
    }

}  // namespace GameEngine
