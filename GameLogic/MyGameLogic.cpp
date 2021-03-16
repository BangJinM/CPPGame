#include "MyGameLogic.h"

#include "AssetLoader.h"
#include "Camera.h"
#include "GameObject.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Transform.h"

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

        auto trans = m_Scene->GetRootGameObject()->getChildByName("dirLight")->getComponent<Transform>();
        auto lightmat4 = glm::lookAt(trans->GetPosition(), glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
        trans->SetMatrix(lightmat4);

        trans = m_Scene->GetRootGameObject()->getChildByName("cameraObject")->getComponent<Transform>();
        auto camera = glm::lookAt(trans->GetPosition(), glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
        trans->SetMatrix(camera);
        return 0;
    }
    void MyGameLogic::Finalize() {}
    void MyGameLogic::Tick(float deltaTime)
    {
    }

}  // namespace GameEngine
