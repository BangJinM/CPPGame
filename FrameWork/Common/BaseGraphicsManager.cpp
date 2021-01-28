#include <iostream>
#include "BaseGraphicsManager.h"
#include "AssetLoader.h"
#include "Scene.h"
#include "Camera.h"
#include "Render/Draw/ForwardDrawPass.h"
#include "SceneManager.h"
using namespace std;

GameEngineBegin

extern SceneManager *g_pSceneManager;
extern GameEngineFile::AssetLoader *g_pAssetLoader;

int BaseGraphicsManager::Initialize()
{
	m_IDrawPass.push_back(std::make_shared<ForwardDrawPass>());
	for (auto pass : m_IDrawPass) {
		pass->Initialize();
	}
    return 0;
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
	for (auto pass : m_IDrawPass) {
		pass->Draw();
	}
}

void BaseGraphicsManager::Tick()
{
    auto scene = g_pSceneManager->GetScene();
    
    for (auto i = scene->m_Cameras.begin(); i != scene->m_Cameras.end(); i++)
    {
        (*i)->Render(scene->m_Renderers);
    }
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
