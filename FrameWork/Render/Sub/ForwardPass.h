#pragma once

#include "../ISubPass.h"
#include "BaseGraphicsManager.h"
#include "Scene.h"
#include "SceneManager.h"
#include "ShaderManager.h"

namespace GameEngine
{
    extern ShaderManager *g_pShaderManager;
    extern BaseGraphicsManager *g_pGraphicsManager;
    extern SceneManager *g_pSceneManager;
    class ForwardPass : public ISubPass
    {
    public:
        virtual void Initialize() override
        {
            m_ShaderID = g_pShaderManager->AddShaderByPath("", "");
        }

        virtual void BeginPass() override
        {
        }

        virtual void Draw() override
        {
            auto m_RendererCommands = g_pGraphicsManager->getRendererCommand();
            auto scene = g_pSceneManager->GetScene();
            auto m_Lights = scene->m_Lights;
            for (auto renderer = m_RendererCommands.begin(); renderer != m_RendererCommands.end(); renderer++)
            {
                g_pGraphicsManager->PrepareMaterial(*renderer);
                g_pGraphicsManager->PrepareMesh(renderer->mesh, renderer->index);
            }
        }

        virtual void EndPass() override
        {
        }

        int m_ShaderID;
    };
}  // namespace GameEngine
