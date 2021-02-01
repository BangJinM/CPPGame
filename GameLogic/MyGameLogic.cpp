#include "MyGameLogic.h"

#include "ParserManager.h"
#include "Scene.h"
#include "SceneManager.h"

namespace GameEngine
{
    extern ParserManager *g_pParserManager;
    extern SceneManager *g_pSceneManager;
    int MyGameLogic::Initialize()
    {
        SharePtr<Scene> m_Scene;
        m_Scene = std::dynamic_pointer_cast<Scene>(g_pParserManager->ExecuteParser(ParserExtType::SCENE, "Scene/defaultEx.scene"));
        g_pSceneManager->SetNextScene(m_Scene);
        return 0;
    }
    void MyGameLogic::Finalize() {}
    void MyGameLogic::Tick() {}

}  // namespace GameEngine
