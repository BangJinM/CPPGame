#pragma once

#include "../ISubPass.h"
#include "GraphicsManager.h"
#include "Cube.h"
#include "Scene.h"
#include "SceneManager.h"
#include "ShaderManager.h"
#include "GraphicsFunc.h"

namespace GameEngine
{
    extern ShaderManager *g_pShaderManager;
    extern SceneManager *g_pSceneManager;
    
    class CubPass : public ISubPass
    {
    public:
        virtual void Initialize() override
        {
            m_ShaderID = g_pShaderManager->AddShaderByPath("Shaders/sampleCube.vert", "Shaders/sampleCube.frag");
        }

        virtual void BeginDraw() override
        {
        }

        virtual void Draw(SharedCamera camera) override
        {
            auto scene = g_pSceneManager->GetScene();
            auto cube = scene->GetCube();
            if (cube && cube->GetTextureID() <= 0)
                GraphicsFunc::BindCubeTexture(cube);
            GraphicsFunc::DrawCubeTexture(cube, m_ShaderID);
        }

        virtual void EndDraw() override
        {
        }

        int m_ShaderID;
    };
}  // namespace GameEngine
