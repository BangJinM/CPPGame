#include "GameObject.h"
#include "Component.h"
#include "glad/glad.h"
#include "MeshRendererCommand.h"
#include "GraphicsManager.h"

namespace GameEngine
{
    extern GraphicsManager *g_pGraphicsManager;

    void BaseObject::addComponent(Component *component)
    {
        auto begin = m_compenents.find(component->getClassID());
        if (begin != m_compenents.end())
        {
            return;
        }
        m_compenents.insert(std::pair<int, Component *>(component->getClassID(), component));
        component->setHost(this);
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

    GameObject::~GameObject()
    {
        m_Meshs.clear();
        m_Materials.clear();
    }

    void GameObject::Draw(GlmMat4 viewMat, GlmMat4 projectMat)
    {
        auto modelMat = getComponent<Transform>()->getMatrix();
        for (size_t i = 0; i < m_Meshs.size(); i++)
        {
            MeshRendererCommand* renderer = new MeshRendererCommand();
            if (m_Materials.size() > i && m_Materials[i])
            {	
				Material *material = new Material(m_Materials[i]);
				material->AddProperty<GlmMat4>(projectMat, "projection", MaterialType::Mat4);
				material->AddProperty<GlmMat4>(viewMat, "view", MaterialType::Mat4);
				material->AddProperty<GlmMat4>(modelMat, "model", MaterialType::Mat4);
				material->use();
				renderer->material = material;
            }
			renderer->material->use();
            renderer->m_Vao = m_Meshs[i]->VAO;
            renderer->m_Mode = GL_TRIANGLES;
            renderer->m_Count = m_Meshs[i]->m_MeshData->indices.size();
            renderer->m_Yype = GL_UNSIGNED_INT;
			
            g_pGraphicsManager->addRendererCommand(renderer);
        }
    }
} // namespace GameEngine