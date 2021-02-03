#include "Transform.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

#include "Utils/SerializableHelper.h"

namespace GameEngine
{
    Transform::Transform() : Component(ClassID(Transform))
    {
        m_Position = VecterFloat3(0, 0, 0);
        m_Scale = VecterFloat3(1, 1, 1);
        m_Rotation = VecterFloat3(0, 0, 0);
        m_Matrix = GlmMat4(1.0f);
        setMatrix(m_Position, m_Scale, m_Rotation);
    }

    void Transform::SetPosition(VecterFloat3 position)
    {
        m_Position = position;
        setMatrix(m_Position, m_Scale, m_Rotation);
    }
    void Transform::SetScale(VecterFloat3 scale)
    {
        m_Scale = scale;
        setMatrix(m_Position, m_Scale, m_Rotation);
    }
    void Transform::SetRotation(VecterFloat3 rotation)
    {
        m_Rotation = rotation;
        setMatrix(m_Position, m_Scale, m_Rotation);
    }
    void Transform::setMatrix(VecterFloat3 position, VecterFloat3 scale, VecterFloat3 rotation)
    {
        m_Matrix = GlmMat4(1.0f);
        m_Matrix = glm::translate(m_Matrix, position);
        m_Matrix = glm::scale(m_Matrix, scale);
        glm::qua<float> q = glm::qua<float>(glm::radians(rotation));  //创建一个四元数
        m_Matrix = glm::mat4_cast(q) * m_Matrix;                      //得到一个旋转的模型矩阵
    }

    void Transform::OnSerialize(cJSON *root)
    {
        cJSON *monitor = cJSON_AddObjectToObject(root, "Transform");
        SerializableHelper::Seserialize(monitor, "rotation", m_Rotation);
        SerializableHelper::Seserialize(monitor, "position", m_Position);
        SerializableHelper::Seserialize(monitor, "scale", m_Scale);
        Component::OnSerialize(monitor);
    }

    void Transform::OnDeserialize(cJSON *root)
    {
        SetRotation(SerializableHelper::DeserializeVecterFloat3(root, "rotation"));
        SetPosition(SerializableHelper::DeserializeVecterFloat3(root, "position"));
        SetScale(SerializableHelper::DeserializeVecterFloat3(root, "scale"));
        Component::OnDeserialize(root);
    }

}  // namespace GameEngine
