#include "GameObject.h"
#include "Component.h"
namespace GameEngine
{
    Component *BaseObject::addComponent(Component *component)
    {
        return nullptr;
    }

    void BaseObject::addChild(BaseObject *child)
    {
    }

    void BaseObject::getChildByName()
    {
    }

    void BaseObject::deleteChild(BaseObject *child)
    {
    }

    BaseObject::BaseObject()
    {
    }

    Component *BaseObject::getComponentBy(int classID)
    {
        auto itor = m_compenents.find(classID);
        if (itor != m_compenents.cend())
        {
            return itor->second;
        }
        return nullptr;
    }
} // namespace GameEngine