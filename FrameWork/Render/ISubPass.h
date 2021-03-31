#pragma once

#include "IPass.h"

namespace GameEngine
{
    class ISubPass : public IPass
    {
    public:
        virtual void Initialize() override {}
        virtual void BeginDraw() override {}
        virtual void Draw(SharedCamera) override {}
        virtual void EndDraw() override {}
    };
}  // namespace GameEngine