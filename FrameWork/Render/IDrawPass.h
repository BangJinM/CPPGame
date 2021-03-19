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
        virtual void Initialize() override;

        virtual void BeginDraw() override;

        virtual void Draw() override;

        virtual void EndDraw() override;

    protected:
        IDrawPass() = default;

    protected:
        std::vector<std::shared_ptr<ISubPass>> m_SubPasses;
    };
}  // namespace GameEngine
