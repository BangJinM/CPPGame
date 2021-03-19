#pragma once

#include "../ISubPass.h"
#include "GraphicsManager.h"
#include "Scene.h"
#include "SceneManager.h"
#include "ShaderManager.h"
#include "GraphicsFunc.h"

namespace GameEngine
{
    extern ShaderManager *g_pShaderManager;
    extern GraphicsManager *g_pGraphicsManager;
    extern SceneManager *g_pSceneManager;
    class ForwardPass : public ISubPass
    {
    public:
        virtual void Initialize() override
        {
        }

        virtual void BeginDraw() override
        {
        }

        virtual void Draw() override
        {
             auto m_RendererCommands = g_pGraphicsManager->GetRendererCommand();
             auto scene = g_pSceneManager->GetScene();
             auto m_Lights = scene->m_Lights;
			 Frame& frame = g_pGraphicsManager->GetFrame();
             for (auto renderer : m_RendererCommands)
             {
                 GraphicsFunc::PrepareMaterial(renderer.second.material, frame);
                 for (auto config : renderer.second.modelConfigs)
                 {
                     GraphicsFunc::SetModelInfos(config.modelInfos, frame);
                     auto shader = g_pShaderManager->GetShaderProgram(renderer.second.material->shaderID);
                     GraphicsFunc::SetUBOData(shader, frame);
                     GraphicsFunc::PrepareMesh(config);
                 }
             }
        }

        virtual void EndDraw() override
        {
        }

        int m_ShaderID;
    };
}  // namespace GameEngine
