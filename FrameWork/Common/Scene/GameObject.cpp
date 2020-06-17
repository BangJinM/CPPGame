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
        m_Mesh = nullptr;
    }
    void GameObject::draw()
    {
        if (m_Mesh != nullptr)
        {
            // Allocate an OpenGL vertex array object.
            GLuint vao;
            glGenVertexArrays(1, &vao);

            // Bind the vertex array object to store all the buffers and vertex attributes we create here.
            glBindVertexArray(vao);

            GLuint buffer_id;

            
        }
    }
} // namespace GameEngine