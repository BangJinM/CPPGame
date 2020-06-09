#include "GameObject.h"
#include "Component.h"
namespace GameEngine
{
    Component *GameObject::addComponent(Component *component)
    {
        return nullptr;
    }

    void GameObject::addChild(GameObject *child)
    {
    }

    void GameObject::getChildByName()
    {
    }

    void GameObject::deleteChild(GameObject *child)
    {
    }

    GameObject::GameObject()
    {
    }

    Component *GameObject::getComponentBy(int classID)
    {
        auto itor = m_compenents.find(classID);
        if (itor != m_compenents.cend())
        {
            return itor->second;
        }
        return nullptr;
    }
} // namespace GameEngine