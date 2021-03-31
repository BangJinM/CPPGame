#pragma once

#include "../ISubPass.h"
#include "ShaderManager.h"

namespace GameEngine
{
    extern ShaderManager *g_pShaderManager;
    class DeferredPass : public ISubPass
    {
    public:
        virtual void Initialize() override
        {
            // m_ShaderID = g_pShaderManager->AddShaderByPath("", "");
        }

        virtual void BeginDraw() override {}

        virtual void Draw(SharedCamera camera) override {}

        virtual void EndDraw() override {}

        int m_ShaderID;
    };
}  // namespace GameEngine
