#include "GameObject.h"
#include "Component.h"
#include "glad/glad.h"
namespace GameEngine
{
    void BaseObject::addComponent(Component *component)
    {
        auto begin = m_compenents.find(component->getClassID());
        if (begin != m_compenents.end())
        {
            return;
        }
        m_compenents.insert(std::pair<int, Component *>(component->getClassID(), component));
    }

    void BaseObject::addChild(BaseObject *child)
    {
        auto begin = m_children.find(child->getName());
        if (begin != m_children.end())
        {
            return;
        }
        m_children.insert(std::pair<std::string, BaseObject *>(child->getName(), child));
    }

    BaseObject *BaseObject::getChildByName(std::string name)
    {
        auto begin = m_children.find(name);
        if (begin != m_children.end())
        {
            return begin->second;
        }
        return nullptr;
    }

    void BaseObject::deleteChild(BaseObject *child)
    {
        auto begin = m_children.find(child->getName());
        if (begin != m_children.end())
        {
            m_children.erase(child->getName());
        }
    }

    BaseObject::BaseObject()
    {
    }

    Component *BaseObject::getComponentBy(int classID)
    {
        auto itor = m_compenents.find(classID);
        if (itor != m_compenents.end())
        {
            return itor->second;
        }
        return nullptr;
    }
    GameObject::GameObject()
    {
        m_Transfrom = new Transform();
    }

    void GameObject::Draw()
    {
        for (size_t i = 0; i < m_Meshs.size(); i++)
        {
            if (m_Materials[i])
            {
                m_Materials[i]->use();
            }
            m_Meshs[i]->Draw();
        }
    }
} // namespace GameEngine