#ifndef GameEngine_Common_Scene_Component_H
#define GameEngine_Common_Scene_Component_H

#include "ClassIDs.h"
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

        void setHost(GameObject *host)
        {
            m_Host = host;
        }

    public:
        GameObject *m_Host; //寄主
    };
} // namespace GameEngine
#endif