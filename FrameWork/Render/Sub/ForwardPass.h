#pragma once

#include "../ISubPass.h"

#include "ShaderManager.h"

namespace GameEngine
{
    extern ShaderManager *g_pShaderManager;
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

        virtual void Draw() override {

        }

        virtual void EndPass() override
        {

        }

        int m_ShaderID;
    };
} // namespace GameEngine
