#include "GameObject.h"
#include "Component.h"
#include "MeshRenderer.h"
#include "BaseGraphicsManager.h"
#include "Transform.h"
#include <glm/gtc/type_ptr.hpp>

GameEngineBegin

    SharedGameObject

    GameObject::createGameObject()
{
    auto obj = std::make_shared<GameObject>();
    obj->m_GameObject = obj;

    obj->addComponent<Transform>(std::make_shared<Transform>());

    return obj;
}

void GameObject::addChild(SharedGameObject child)
{
    auto begin = m_children.find(child->getName());
    if (begin != m_children.end())
    {
        return;
    }
    child->setParent(m_GameObject.lock());
    m_children.insert(std::pair<std::string, SharedGameObject>(child->getName(), child));
}

SharedGameObject GameObject::getChildByName(std::string name)
{
    auto begin = m_children.find(name);
    if (begin != m_children.end())
    {
        return begin->second;
    }
    return nullptr;
}

SharedGameObject GameObject::getChildByID(int id)
{
    for (auto child = m_children.begin(); child != m_children.end(); child++)
    {
        if (child->second->GetFileID() == id)
        {
            return child->second;
        }
        else
        {
            auto res = child->second->getChildByID(id);
            if (res)
                return res;
        }
    }

    return nullptr;
}

void GameObject::deleteChild(SharedGameObject child)
{
    auto begin = m_children.find(child->getName());
    if (begin != m_children.end())
    {
        m_children.erase(child->getName());
    }
}

void GameObject::setParent(SharedGameObject parent)
{
    m_Parent = parent;
}

SharedGameObject GameObject::getParent()
{
    return m_Parent;
}

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
    m_compenents.clear();
    m_children.clear();
}

void GameObject::setName(std::string name)
{
    m_Name = name;
}

void GameObject::Start()
{
    for (auto i = m_compenents.begin(); i != m_compenents.end(); i++)
    {
        (*i)->Start();
    }
    for (auto i = m_children.begin(); i != m_children.end(); i++)
    {
        i->second->Start();
    }
}

void GameObject::Update()
{
    for (auto i = m_compenents.begin(); i != m_compenents.end(); i++)
    {
        (*i)->Update();
    }
    for (auto i = m_children.begin(); i != m_children.end(); i++)
    {
        i->second->Update();
    }
}

void GameObject::Destory()
{
    for (auto i = m_compenents.begin(); i != m_compenents.end(); i++)
    {
        (*i)->Destory();
    }
    for (auto i = m_children.begin(); i != m_children.end(); i++)
    {
        i->second->Destory();
    }
}

GameEngineEnd