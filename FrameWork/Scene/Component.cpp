#include "Component.h"

#include "GameObject.h"

namespace GameEngine
{
    ClassIDType Component::getClassID()
    {
        if (m_ClassID > 0)
            return m_ClassID;
        return ClassIDType::CLASS_Undefined;
    }

    void Component::SetParent(SharedGameObject host)
    {
        if (m_Parent.lock() != host)
        {
            m_Parent = host;
        }
    }

    SharedGameObject Component::GetParent()
    {
        return m_Parent.lock();
    }

    void Component::OnSerialize(cJSON* root)
    {
        Object::OnSerialize(root);
    }
    void Component::OnDeserialize(cJSON* root)
    {
        Object::OnDeserialize(root);
    }

    void Component::Start()
    {
        if (m_Started)
            return;
        m_Started = true;
    }

    void Component::Update() {}
    void Component::Destory() {}
    void Component::OnEnable() { m_Enable = true; }

}  // namespace GameEngine