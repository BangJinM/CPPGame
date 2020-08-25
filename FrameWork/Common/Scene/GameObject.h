#ifndef GameEngine_Common_Scene_Object_H
#define GameEngine_Common_Scene_Object_H

#include "ClassIDs.h"
#include <map>
#include <list>
#include "Mesh.h"
#include "Material.h"
#include "Transform.h"
#include "Object.h"

namespace GameEngine
{
    class Material;

    class GameObject : public Object
    {
        friend class Component;

    public:
		static std::shared_ptr<GameObject> createGameObject();
        template <class T>
        std::shared_ptr<T> getComponent();
        template <class T>
        std::shared_ptr<T> addComponent(std::shared_ptr<T> component);
        template <class T>
        std::shared_ptr<T> addComponent(T *component);

        void addChild(std::shared_ptr<GameObject> child);
        void deleteChild(std::shared_ptr<GameObject> child);

        void setName(std::string name);

        std::shared_ptr<GameObject> getChildByName(std::string name);
        std::shared_ptr<GameObject> getParent();
        void setParent(std::shared_ptr<GameObject> parent);

        GameObject();
        void Update();
        virtual ~GameObject();

        std::string getName()
        {
            return m_Name;
        }

        std::map<std::string, std::shared_ptr<GameObject>> getChildren()
        {
            return m_children;
        }

    private:
        std::vector<std::shared_ptr<Component>> m_compenents;
        std::shared_ptr<GameObject> m_Parent;
        std::map<std::string, std::shared_ptr<GameObject>> m_children;
        std::string m_Name;

    public:
        //private:
        bool m_isVisual = true;
        std::shared_ptr<Mesh> m_Mesh;
		std::weak_ptr<GameObject> m_GameObject;
        std::vector<std::shared_ptr<Material>> m_Materials;
    };

    template <class T>
    inline std::shared_ptr<T> GameObject::getComponent()
    {
        for (int i = 0; i < m_compenents.size(); ++i)
        {
            auto &com = m_compenents[i];
            auto t = std::dynamic_pointer_cast<T>(com);
            if (t)
            {
                return t;
            }
        }
        return std::shared_ptr<T>();
    }
    template <class T>
    inline std::shared_ptr<T> GameObject::addComponent(std::shared_ptr<T> component)
    {
        if (component)
        {
            component->InitComponent(m_GameObject.lock());
            m_compenents.push_back(component);
			return component;
        }
		return std::shared_ptr<T>();
    }

    template <class T>
    inline std::shared_ptr<T> GameObject::addComponent(T *component)
    {
        std::shared_ptr<T> t = std::shared_ptr<T>(component);
        auto com = addComponent<T>(t);
        return com;
    }

} // namespace GameEngine
#endif