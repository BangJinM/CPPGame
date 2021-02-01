#pragma once

#include "IPass.h"

namespace GameEngine
{
    class ISubPass : public IPass
    {
    public:
        virtual void Initialize() override {}
        virtual void BeginPass() override {}
        virtual void Draw() override {}
        virtual void EndPass() override {}
    };
}  // namespace GameEngine