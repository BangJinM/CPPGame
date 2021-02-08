﻿#include "BaseGraphicsManager.h"

#include <iostream>

#include "AssetLoader.h"
#include "Camera.h"
#include "GameObject.h"
#include "Render/Draw/ForwardDrawPass.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Transform.h"
using namespace std;

namespace GameEngine
{
    extern SceneManager *g_pSceneManager;
    extern AssetLoader *g_pAssetLoader;

    int BaseGraphicsManager::Initialize()
    {
        m_IDrawPass.push_back(std::make_shared<ForwardDrawPass>());
        for (auto pass : m_IDrawPass)
        {
            pass->Initialize();
        }
        return 0;
    }

    void BaseGraphicsManager::Finalize() {}

    void BaseGraphicsManager::Clear() { m_RendererCommands.clear(); }

    void BaseGraphicsManager::Draw()
    {
        for (auto pass : m_IDrawPass)
        {
            pass->Draw();
        }
    }

    void BaseGraphicsManager::Tick(float deltaTime)
    {
        auto scene = g_pSceneManager->GetScene();

        for (auto camera : scene->m_Cameras)
        {
            auto cameraTs = camera->getParent()->getComponent<Transform>();
            ViewInfos viewInfos;
            viewInfos.cameraPos = cameraTs->GetPosition();
            viewInfos.project = camera->getProjectionMatrix();
            viewInfos.view = cameraTs->getMatrix();

            for (auto render : scene->m_Renderers)
            {
                render->Render(viewInfos);
            }
        }
        Draw();
        m_RendererCommands.clear();
    }

    void BaseGraphicsManager::addRendererCommand(RendererCammand command)
    {
        m_RendererCommands.push_back(command);
    }

    std::list<RendererCammand> BaseGraphicsManager::getRendererCommand()
    {
        return m_RendererCommands;
    }

}  // namespace GameEngine
