#pragma once

#include <memory>
#include <vector>

#include "IPass.h"
#include "ISubPass.h"

namespace GameEngine
{
    class IDrawPass : public IPass
    {
    public:
        void Initialize() override {}

        void BeginPass() override
        {
            for (auto pass : m_SubPasses)
            {
                pass->BeginPass();
            }
        }

        void Draw() override {}

        void EndPass() override
        {
            for (auto pass : m_SubPasses)
            {
                pass->EndPass();
            }
        }

    protected:
        IDrawPass() = default;

    protected:
        std::vector<std::shared_ptr<ISubPass>> m_SubPasses;
    };
}  // namespace GameEngine
