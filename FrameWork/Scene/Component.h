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
        ClassIDType getClassID();

        void SetParent(SharedGameObject host);
        SharedGameObject GetParent();

        virtual void OnSerialize(cJSON* root) override;
        virtual void OnDeserialize(cJSON* root) override;

        virtual void Start() override;
        virtual void OnEnable() override;
        virtual void Update() override;
        virtual void Destory() override;

    public:
        ClassIDType m_ClassID = ClassID(Undefined);

        std::weak_ptr<GameObject> m_Parent;    //寄主
        std::weak_ptr<Component> m_Component;  //自己

        bool m_Enable = true;
        bool m_Started = false;
    };
}  // namespace GameEngine