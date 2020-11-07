#include <iostream>
#include "BaseGraphicsManager.h"
#include "AssetLoader.h"
#include "Scene.h"
#include "Camera.h"
#include "SceneManager.h"
using namespace std;

GameEngineBegin

    extern AssetLoader *g_pAssetLoader;

int BaseGraphicsManager::Initialize()
{
    return 1;
}

void BaseGraphicsManager::Finalize()
{

}

void BaseGraphicsManager::Clear()
{
}

void BaseGraphicsManager::Draw()
{
}

void BaseGraphicsManager::Tick()
{
    SceneManager::GetInstance()->ChangeScene();
    SceneManager::GetInstance()->Update();
    Draw();
}

void BaseGraphicsManager::addRendererCommand(RendererCammand command)
{
    m_RendererCommands.push_back(command);
}

GameEngineEnd