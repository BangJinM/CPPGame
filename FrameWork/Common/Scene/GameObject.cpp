#include "GameObject.h"
#include "Component.h"
#include "glad/glad.h"
#include "MeshRenderer.h"
#include "GraphicsManager.h"
#include <glm/gtc/type_ptr.hpp>

namespace GameEngine
{


	std::shared_ptr<GameObject> GameObject::createGameObject()
	{
		auto obj = std::make_shared<GameObject>();
		obj->m_ThisObject = obj;
		return obj;
	}

	void GameObject::addChild(std::shared_ptr<GameObject> child)
    {
        auto begin = m_children.find(child->getName());
        if (begin != m_children.end())
        {
            return;
        }
		child->setParent(m_ThisObject.lock());
        m_children.insert(std::pair<std::string, std::shared_ptr<GameObject>>(child->getName(), child));
    }

    std::shared_ptr<GameObject> GameObject::getChildByName(std::string name)
    {
        auto begin = m_children.find(name);
        if (begin != m_children.end())
        {
            return begin->second;
        }
        return nullptr;
    }

    void GameObject::deleteChild(std::shared_ptr<GameObject> child)
    {
        auto begin = m_children.find(child->getName());
        if (begin != m_children.end())
        {
            m_children.erase(child->getName());
        }
    }

    void GameObject::setParent(std::shared_ptr<GameObject> parent)
    {
        m_Parent = parent;
    }

    std::shared_ptr<GameObject> GameObject::getParent()
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

    void GameObject::Update(){
        for (auto i = m_compenents.begin(); i != m_compenents.end(); i++)
        {
			(*i)->Update();
        }
        for (auto i = m_children.begin(); i != m_children.end(); i++)
        {
			i->second->Update();
        }
    }

} // namespace GameEngine