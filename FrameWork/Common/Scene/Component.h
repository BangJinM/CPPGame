#ifndef GameEngine_Common_Scene_Component_H
#define GameEngine_Common_Scene_Component_H

#include "ClassIDs.h"
#include <memory>
#include "Object.h"
namespace GameEngine
{
    class Component:public Object
    {
        friend class GameObject;

    public:
        ClassIDType getClassID()
        {
            if (m_ClassID > 0)
                return m_ClassID;
            return ClassIDType::CLASS_Undefined;
        }
        ClassIDType m_ClassID = ClassIDType::CLASS_Undefined;

        virtual ~Component()
        {
        }
        Component(ClassIDType classID) : m_ClassID(classID) {}

        void setParent(std::shared_ptr<GameObject> host)
        {
            if (m_Parent.lock() != host)
            {
                m_Parent = host;
            }
        }
        
        std::shared_ptr<GameObject> getParent(){
            return m_Parent.lock();
        }

    public:
        virtual void Start() {}
        virtual void Update() {}
        virtual void LateUpdate() {}
        virtual void OnEnable(bool enable) { m_Enable = enable; }

    public:
        std::weak_ptr<GameObject> m_Parent; //寄主
        bool m_Enable = true;
        bool m_Started = false;
    };
} // namespace GameEngine
#endif