#pragma once

#include "../BaseGraphicsManager.h"
#include "../ISubPass.h"
#include "Scene.h"
#include "SceneManager.h"
#include "ShaderBase.h"
#include "ShaderManager.h"

namespace GameEngine
{
    extern ShaderManager *g_pShaderManager;
    extern BaseGraphicsManager *g_pGraphicsManager;
    extern SceneManager *g_pSceneManager;
    class ShadowPass : public ISubPass
    {
    public:
        virtual void Initialize() override
        {
            m_ShaderID = g_pShaderManager->AddShaderByPath("Shaders/sample_shadow.vert", "Shaders/sample_shadow.frag");
        }

        virtual void BeginPass() override
        {
        }

        virtual void Draw() override
        {
            auto m_RendererCommands = g_pGraphicsManager->GetRendererCommand();
            auto scene = g_pSceneManager->GetScene();
            auto shader = g_pShaderManager->GetShaderProgram(m_ShaderID);
            shader->Use();
            auto m_LightInfos = g_pGraphicsManager->GetLightInfo();
            auto shadowMap = g_pGraphicsManager->GetShadowArray(m_LightInfos.numsLight);
            uint32_t index = 0;
            g_pGraphicsManager->DeleteShadowArrsy();
            for (int i = 0; i < m_LightInfos.numsLight; i++)
            {
                shader->setInt("layer_index", i);
                g_pGraphicsManager->BeginShadow(m_LightInfos, index);
                for (auto renderer : m_RendererCommands)
                {
                    for (auto config : renderer.second.modelConfigs)
                    {
                        g_pGraphicsManager->SetModelInfos(config.modelInfos);
                        g_pGraphicsManager->SetUBOData(shader);
                        g_pGraphicsManager->PrepareMesh(config);
                    }
                }
                g_pGraphicsManager->EndShadow();
                index++;
            }
        }

        virtual void EndPass() override
        {
        }

        int m_ShaderID;
    };
}  // namespace GameEngine
