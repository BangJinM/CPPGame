#include "GameObject.h"
#include "Component.h"
#include "glad/glad.h"
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
    GameObject::GameObject()
    {
        m_Transfrom = new Transform();
        m_Material = nullptr;
    }
    void GameObject::draw()
    {
        for (size_t i = 0; i < m_Meshs.size(); i++)
        {
            m_Meshs[i].Draw();
        }
    }
} // namespace GameEngine