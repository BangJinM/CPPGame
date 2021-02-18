#pragma once

#include "../ISubPass.h"
#include "BaseGraphicsManager.h"
#include "Cube.h"
#include "Scene.h"
#include "SceneManager.h"
#include "ShaderManager.h"

namespace GameEngine
{
    extern ShaderManager *g_pShaderManager;
    extern BaseGraphicsManager *g_pGraphicsManager;
    extern SceneManager *g_pSceneManager;
    
    class CubPass : public ISubPass
    {
    public:
        virtual void Initialize() override
        {
            m_ShaderID = g_pShaderManager->AddShaderByPath("Shaders/sampleCube.vert", "Shaders/sampleCube.frag");
        }

        virtual void BeginPass() override
        {
        }

        virtual void Draw() override
        {
            auto scene = g_pSceneManager->GetScene();
            auto cube = scene->GetCube();
            if (cube && cube->GetTextureID() <= 0)
                g_pGraphicsManager->BindCubeTexture(cube);
            g_pGraphicsManager->DrawCubeTexture(cube, m_ShaderID);
        }

        virtual void EndPass() override
        {
        }

        int m_ShaderID;
    };
}  // namespace GameEngine
