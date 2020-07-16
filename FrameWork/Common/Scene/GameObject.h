#ifndef GameEngine_Common_Scene_Object_H
#define GameEngine_Common_Scene_Object_H

#include "ClassIDs.h"
#include <map>
#include <list>
#include "Mesh.h"
#include "Material.h"
#include "Transform.h"

namespace GameEngine
{
    class BaseObject;
    class MeshDatas;
    class Material;

    class BaseObject
    {

        friend class Component;

    public:
        template <class T>
        inline T *getComponent();

        void addComponent(Component *component);

        void addChild(BaseObject *child);

        BaseObject * getChildByName(std::string name);

        void deleteChild(BaseObject *child);

        void setParent(BaseObject *parent)
        {
            m_Parent = parent;
        }

        BaseObject *getParent()
        {
            return m_Parent;
        }

        BaseObject();
		virtual ~BaseObject()
		{
            for (auto i = m_children.begin(); i != m_children.end(); i++)
            {
                delete i->second;
            }
            for (auto i = m_compenents.begin(); i != m_compenents.end(); i++)
            {
                delete i->second;
            }
            m_compenents.clear();
            m_children.clear();
		}
        void setName(std::string name)
        {
            m_Name = name;
        }

        std::string getName() { return m_Name; }

		std::map<std::string, BaseObject *> getChildren() {
			return m_children;
		}
    private:
        Component *getComponentBy(int classID);

    private:
        std::map<int, Component *> m_compenents;

        BaseObject *m_Parent;

        std::map<std::string, BaseObject *> m_children;

        std::string m_Name;
    };

    class GameObject : public BaseObject
    {
    public:
        GameObject();
		//GameObject(const GameObject& gameObject);
		virtual ~GameObject();
        void Draw(GlmMat4 viewMat, GlmMat4 projectMat);

        //private:
        bool m_isVisual = true;
        std::vector<Mesh *> m_Meshs;
        std::vector<Material *> m_Materials;
    };

    template <class T>
    inline T *BaseObject::getComponent()
    {
        T compenent = T();
        Component *t = dynamic_cast<Component *>(&compenent);
        if (t)
        {
            auto itor = m_compenents.find(compenent.getClassID());
            if (itor != m_compenents.end())
            {
                return static_cast<T *>(itor->second);
            }
        }
        return nullptr;
    }
} // namespace GameEngine
#endif