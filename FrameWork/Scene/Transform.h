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
        Transform(ClassIDType classID = ClassID(Transform));

        void SetPosition(VecterFloat3 position);
        void SetScale(VecterFloat3 scale);
        void SetRotation(VecterFloat3 rotation);
        void setMatrix(VecterFloat3 position, VecterFloat3 scale, VecterFloat3 rotation);

        GlmMat4 getMatrix() { return m_Matrix; }

        virtual void OnSerialize(cJSON *root) override;
        virtual void OnDeserialize(cJSON *root) override;

    private:
        GlmMat4 m_Matrix;

        VecterFloat3 m_Position;
        VecterFloat3 m_Scale;
        VecterFloat3 m_Rotation;
    };
}  // namespace GameEngine
