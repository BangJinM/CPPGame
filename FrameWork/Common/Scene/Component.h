#ifndef GameEngine_Common_Scene_Component_H
#define GameEngine_Common_Scene_Component_H

#include "ClassIDs.h"
namespace GameEngine
{
    class Component
    {
        friend class BaseObject;

    public:
        ClassIDType getClassID()
        {
            if (m_ClassID > 0)
                return m_ClassID;
            return ClassIDType::CLASS_Undefined;
        }
        ClassIDType m_ClassID = ClassIDType::CLASS_Undefined;

        Component(ClassIDType classID) : m_ClassID(classID) {}

        void setHost(BaseObject *host)
        {
            m_Host = host;
        }

    public:
        BaseObject *m_Host; //寄主
    };
} // namespace GameEngine
#endif