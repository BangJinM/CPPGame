#pragma once

#include <map>
#include <string>
#include <vector>

#include "Component.h"
#include "Config.h"
#include "ISerializable.h"
#include "MyMath.h"
#include "cjson/cJSON.h"

namespace GameEngine
{
    class Transform : public Component
    {
    public:
        Transform();

        void SetPosition(VecterFloat3 position);
        VecterFloat3 GetPosition() { return m_Position; }

        void SetScale(VecterFloat3 scale);
        VecterFloat3 GetScale() { return m_Scale; }

        void SetRotation(VecterFloat3 rotation);
        VecterFloat3 GetRotation() { return m_Rotation; }

        void SetMatrix(VecterFloat3 position, VecterFloat3 scale, VecterFloat3 rotation);
        GlmMat4 GetMatrix() { return m_Matrix; }

        GlmMat4 GetViewMatrix() { return m_InverseMatrix; }

        void SetParentPosition(VecterFloat3 pos);

        virtual void OnSerialize(cJSON *root) override;
        virtual void OnDeserialize(cJSON *root) override;

        VecterFloat3 GetForward() { return m_Front; }
        VecterFloat3 GetUp() { return m_Up; }
        VecterFloat3 GetRight() { return m_Right; }

    private:
        GlmMat4 m_Matrix;
        GlmMat4 m_InverseMatrix;

        VecterFloat3 m_V3ParentPosition;

        VecterFloat3 m_Position;
        VecterFloat3 m_Scale;
        VecterFloat3 m_Rotation;

        VecterFloat3 m_Front;
        VecterFloat3 m_Right;
        VecterFloat3 m_Up;
    };
}  // namespace GameEngine
