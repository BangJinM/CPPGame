#include "ShadowPass.h"

#include "../GraphicsManager.h"
#include "Scene.h"
#include "SceneManager.h"
#include "ShaderBase.h"
#include "ShaderManager.h"
#include "GraphicsFunc.h"

namespace GameEngine
{
    extern ShaderManager *g_pShaderManager;
    extern GraphicsManager *g_pGraphicsManager;
    extern SceneManager *g_pSceneManager;
    void ShadowPass::Initialize()
    {
        m_ShaderID = g_pShaderManager->AddShaderByPath("Shaders/sample_shadow.vert", "Shaders/sample_shadow.frag");
    }

    void ShadowPass::BeginDraw()
    {
    }

    void ShadowPass::Draw()
    {
        auto m_RendererCommands = g_pGraphicsManager->GetRendererCommand();
        auto shader = g_pShaderManager->GetShaderProgram(m_ShaderID);
        shader->Use();
        Frame& frame = g_pGraphicsManager->GetFrame();
        auto m_LightInfos = g_pGraphicsManager->GetLightInfo();
        GraphicsFunc::GetShadowArray(m_LightInfos.numsLight, frame);
        uint32_t index = 0;
        for (int i = 0; i < m_LightInfos.numsLight; i++)
        {
            shader->setInt("layer_index", i);
            GraphicsFunc::BeginShadow(m_LightInfos, index, frame);
            for (auto renderer : m_RendererCommands)
            {
                for (auto config : renderer.second.modelConfigs)
                {
                    GraphicsFunc::SetModelInfos(config.modelInfos, frame);
                    GraphicsFunc::SetUBOData(shader, frame);
                    GraphicsFunc::PrepareMesh(config);
                }
            }
            GraphicsFunc::EndShadow(frame);
            index++;
        }
    }

    void ShadowPass::EndDraw()
    {
    }

}  // namespace GameEngine