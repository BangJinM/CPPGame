#pragma once

#include "../ISubPass.h"

namespace GameEngine
{
    class ShadowPass : public ISubPass
    {
    public:
        virtual void Initialize() override;
        virtual void BeginDraw() override;
        virtual void Draw(SharedCamera camera) override;
        virtual void EndDraw() override;

    private:
        int m_ShaderID;
        int m_ShaderID2;
    };
}  // namespace GameEngine
