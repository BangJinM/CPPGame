#include "MyGameLogic.h"
#include "Scene.h"
#include "ParserManager.h"
#include "SceneManager.h"

GameEngineBegin extern GameEngineParser::ParserManager *g_pParserManager;
int MyGameLogic::Initialize()
{
    SharePtr<Scene> m_Scene;
    m_Scene = std::dynamic_pointer_cast<Scene>(g_pParserManager->ExecuteParser(GameEngineParser::ParserExtType::SCENE, "Scene/defaultEx.scene"));
    SceneManager::GetInstance()->SetNextScene(m_Scene);
    return 0;
}
void MyGameLogic::Finalize() {}
void MyGameLogic::Tick() {}

GameEngineEnd
