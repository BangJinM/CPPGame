#include "GameObject.h"
#include "Component.h"
#include "glad/glad.h"
#include "MeshRendererCommand.h"
#include "GraphicsManager.h"
#include <glm/gtc/type_ptr.hpp>

namespace GameEngine
{
    extern GraphicsManager *g_pGraphicsManager;

    void GameObject::addComponent(Component *component)
    {
        auto begin = m_compenents.find(component->getClassID());
        if (begin != m_compenents.end())
        {
            return;
        }
        component->setHost(this);
        m_compenents.insert(std::pair<int, Component *>(component->getClassID(), component));
    }

    void GameObject::addChild(GameObject *child)
    {
        auto begin = m_children.find(child->getName());
        if (begin != m_children.end())
        {
            return;
        }
        m_children.insert(std::pair<std::string, GameObject *>(child->getName(), child));
    }

    GameObject *GameObject::getChildByName(std::string name)
    {
        auto begin = m_children.find(name);
        if (begin != m_children.end())
        {
            return begin->second;
        }
        return nullptr;
    }

    void GameObject::deleteChild(GameObject *child)
    {
        auto begin = m_children.find(child->getName());
        if (begin != m_children.end())
        {
            m_children.erase(child->getName());
        }
    }

    void GameObject::setParent(GameObject *parent)
    {
        m_Parent = parent;
    }

    GameObject *GameObject::getParent()
    {
        return m_Parent;
    }

    GameObject::GameObject()
    {
    }

    Component *GameObject::getComponentBy(int classID)
    {
        auto itor = m_compenents.find(classID);
        if (itor != m_compenents.end())
        {
            return itor->second;
        }
        return nullptr;
    }

    GameObject::~GameObject()
    {
        for (auto i = m_children.begin(); i != m_children.end(); i++)
        {
            delete i->second;
        }
        for (auto i = m_compenents.begin(); i != m_compenents.end(); i++)
        {
            delete i->second;
        }
        for (size_t i = 0; i < m_Materials.size(); i++)
        {
            delete m_Materials[i];
        }
        m_Materials.clear();
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
                MeshRendererCommand *renderer = new MeshRendererCommand();
                if (m_Materials.size() > i && m_Materials[i])
                {
                    renderer->material = new Material(*m_Materials[i]);
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