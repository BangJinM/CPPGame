#ifndef GameEngine_Common_Scene_Component_H
#define GameEngine_Common_Scene_Component_H

#include "ClassIDs.h"
#include <memory>
namespace GameEngine
{
    class Component
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

        Component(ClassIDType classID) : m_ClassID(classID) {}

        void setHost(std::shared_ptr<GameObject> host)
        {
            m_Host = host;
        }

    protected:
        virtual void Start() {}
        virtual void Update() {}
        virtual void LateUpdate() {}
        virtual void OnEnable(bool enable) { m_Enable = enable; }

    public:
        std::shared_ptr<GameObject> m_Host; //寄主
        bool m_Enable = true;
        bool m_Started = false;
    };
} // namespace GameEngine
#endif