#include "IDrawPass.h"

namespace GameEngine
{
    void IDrawPass::Initialize()
    {
        for (auto pass : m_SubPasses)
        {
            pass->Initialize();
        }
    }

    void IDrawPass::BeginDraw()
    {
        for (auto pass : m_SubPasses)
        {
            pass->BeginDraw();
        }
    }

    void IDrawPass::Draw()
    {
        for (auto pass : m_SubPasses)
        {
            pass->Draw();
        }
    }

    void IDrawPass::EndDraw()
    {
        for (auto pass : m_SubPasses)
        {
            pass->EndDraw();
        }
    }
}  // namespace GameEngine