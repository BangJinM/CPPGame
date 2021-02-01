#pragma once

#include "../ISubPass.h"
#include "BaseGraphicsManager.h"
#include "ShaderManager.h"

namespace GameEngine
{
    extern ShaderManager *g_pShaderManager;
    extern BaseGraphicsManager *g_pGraphicsManager;
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
            for (auto renderer = m_RendererCommands.begin(); renderer != m_RendererCommands.end(); renderer++)
            {
                g_pGraphicsManager->PrepareMaterial(renderer->material);
                g_pGraphicsManager->PrepareMesh(renderer->mesh, renderer->index);
            }
        }

        virtual void EndPass() override
        {
        }

        int m_ShaderID;
    };
}  // namespace GameEngine
