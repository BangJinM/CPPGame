#pragma once

namespace GameEngine
{
    class IPass
    {
    public:
        virtual void Initialize() = 0;
        virtual void BeginPass() = 0;
        virtual void Draw() = 0;
        virtual void EndPass() = 0;
    };
}  // namespace GameEngine