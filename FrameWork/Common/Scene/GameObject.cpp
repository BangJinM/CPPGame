#include "GameObject.h"
#include "Component.h"
#include "glad/glad.h"
#include "MeshRendererCommand.h"
#include "GraphicsManager.h"
#include <glm/gtc/type_ptr.hpp>

namespace GameEngine
{
    extern GraphicsManager *g_pGraphicsManager;

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

    void GameObject::Draw(GlmMat4 viewMat, GlmMat4 projectMat)
    {
        auto modelMat = getComponent<Transform>()->getMatrix();
        if (m_Mesh)
            for (size_t i = 0; i < m_Mesh->m_MeshDatas.size(); i++)
            {
                std::shared_ptr<MeshRendererCommand> renderer = std::shared_ptr<MeshRendererCommand>( new MeshRendererCommand());
                if (m_Materials.size() > i && m_Materials[i])
                {
                    renderer->material = Material::createMaterial(m_Materials[i]);
                    renderer->material->AddProperty(glm::value_ptr(projectMat), "projection", 16 * sizeof(float), MaterialType::Mat4);
                    renderer->material->AddProperty(glm::value_ptr(viewMat), "view", 16 * sizeof(float), MaterialType::Mat4);
                    renderer->material->AddProperty(glm::value_ptr(modelMat), "model", 16 * sizeof(float), MaterialType::Mat4);
                }
                renderer->m_Vao = m_Mesh->m_MeshDatas[i].VAO;
                renderer->m_Mode = GL_TRIANGLES;
                renderer->m_Count = m_Mesh->m_MeshDatas[i].indices.size();
                renderer->m_Yype = GL_UNSIGNED_INT;

                g_pGraphicsManager->addRendererCommand(renderer);
            }
    }
} // namespace GameEngine