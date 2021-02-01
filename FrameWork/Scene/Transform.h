#pragma once

#include <map>
#include <string>
#include <vector>

#include "Component.h"
#include "Config.h"
#include "MyMath.h"

namespace GameEngine
{
    class Transform : public Component
    {
    public:
        Transform();

        void setPosition(vecterFloat3 position);
        void setScale(vecterFloat3 scale);
        void setRotation(vecterFloat3 rotation);
        void setMatrix(vecterFloat3 position, vecterFloat3 scale, vecterFloat3 rotation);

        GlmMat4 getMatrix() { return m_Matrix; }

    private:
        GlmMat4 m_Matrix;

        vecterFloat3 m_Position;
        vecterFloat3 m_Scale;
        vecterFloat3 m_Rotation;
    };
}  // namespace GameEngine
