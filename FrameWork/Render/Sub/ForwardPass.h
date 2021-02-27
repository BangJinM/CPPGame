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
        }

        virtual void BeginPass() override
        {
        }

        virtual void Draw() override
        {
            auto m_RendererCommands = g_pGraphicsManager->GetRendererCommand();
            auto scene = g_pSceneManager->GetScene();
            auto m_Lights = scene->m_Lights;
            for (auto renderer : m_RendererCommands)
            {
                g_pGraphicsManager->PrepareMaterial(renderer.second.material);
                for (auto config : renderer.second.modelConfigs)
                {
                    g_pGraphicsManager->SetModelInfos(config.modelInfos);
                    auto shader = g_pShaderManager->GetShaderProgram(renderer.second.material->shaderID);
                    g_pGraphicsManager->SetUBOData(shader);
                    g_pGraphicsManager->PrepareMesh(config);
                }
            }
        }

        virtual void EndPass() override
        {
        }

        int m_ShaderID;
    };
}  // namespace GameEngine
