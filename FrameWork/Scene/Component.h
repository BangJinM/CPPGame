#pragma once

#include <memory>

#include "ClassIDs.h"
#include "Config.h"
#include "IBehaviour.h"
#include "Object.h"

namespace GameEngine
{
    class GameObject;

    class Component : public Object, public IBehaviour
    {
        friend class GameObject;

    public:
        ClassIDType getClassID()
        {
            if (m_ClassID > 0)
                return m_ClassID;
            return ClassIDType::CLASS_Undefined;
        }
        ClassIDType m_ClassID = ClassID(Undefined);

        virtual ~Component()
        {
        }
        Component(ClassIDType classID) : m_ClassID(classID) {}

        void setParent(SharedGameObject host)
        {
            if (m_Parent.lock() != host)
            {
                m_Parent = host;
            }
        }

        SharedGameObject getParent()
        {
            return m_Parent.lock();
        }

        virtual void OnSerialize(cJSON* root) override
        {
            Object::OnSerialize(root);
        }
        virtual void OnDeserialize(cJSON* root) override
        {
            Object::OnDeserialize(root);
        }

    public:
        virtual void Start() override
        {
            if (m_Started)
                return;
            m_Started = true;
        }
        virtual void Update() override {}
        virtual void Destory() override {}
        virtual void OnEnable(bool enable) { m_Enable = enable; }
        virtual void SetParent(SharedGameObject host)
        {
            setParent(host);
        }

    public:
        std::weak_ptr<GameObject> m_Parent;    //寄主
        std::weak_ptr<Component> m_Component;  //自己

        bool m_Enable = true;
        bool m_Started = false;
    };
}  // namespace GameEngine