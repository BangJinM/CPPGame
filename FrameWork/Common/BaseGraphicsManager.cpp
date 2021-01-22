#include <iostream>
#include "BaseGraphicsManager.h"
#include "AssetLoader.h"
#include "Scene.h"
#include "Camera.h"
#include "SceneManager.h"
using namespace std;

GameEngineBegin

    extern GameEngineFile::AssetLoader *g_pAssetLoader;

int BaseGraphicsManager::Initialize()
{
    return 1;
}

void BaseGraphicsManager::Finalize()
{

}

void BaseGraphicsManager::Clear()
{
    m_RendererCommands.clear();
}

void BaseGraphicsManager::Draw()
{
}

void BaseGraphicsManager::Tick()
{
    Draw();
}

void BaseGraphicsManager::addRendererCommand(RendererCammand command)
{
    m_RendererCommands.push_back(command);
}

std::list<RendererCammand> BaseGraphicsManager::getRendererCommand()
{
    return m_RendererCommands;
}

GameEngineEnd
