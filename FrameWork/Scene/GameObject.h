#pragma once

#include <list>
#include <map>

#include "ClassIDs.h"
#include "Config.h"
#include "IBehaviour.h"
#include "Material.h"
#include "Mesh.h"
#include "Object.h"
#include "Transform.h"

namespace GameEngine
{
    class Material;

    class GameObject : public Object, public IBehaviour
    {
        friend class Component;

    public:
        virtual void Start() override;
        virtual void Update() override;
        virtual void Destory() override;

        static SharedGameObject createGameObject();
        template <class T>
        SharePtr<T> getComponent();
        template <class T>
        SharePtr<T> addComponent(SharePtr<T> component);
        template <class T>
        void removeComponent(SharePtr<T> component);
        template <class T>
        SharePtr<T> addComponent(T *component);

        void addChild(SharedGameObject child);
        void deleteChild(SharedGameObject child);

        SharedGameObject getChildByName(std::string name);
        SharedGameObject getChildByID(int id);
        SharedGameObject getParent();
        void setParent(SharedGameObject parent);

        virtual void OnSerialize(cJSON* root) override;
        virtual void OnDeserialize(cJSON* root) override;

        GameObject();
        virtual ~GameObject();

        std::map<std::string, SharedGameObject> getChildren()
        {
            return m_children;
        }

    private:
        std::vector<SharePtr<Component>> m_compenents;
        SharedGameObject m_Parent;
        std::map<std::string, SharedGameObject> m_children;

    public:
        //private:
        bool m_isVisual = true;
        SharedMesh m_Mesh;
        std::weak_ptr<GameObject> m_GameObject;
        std::vector<SharedMaterial> m_Materials;
    };

    template <class T>
    inline SharePtr<T> GameObject::getComponent()
    {
        for (unsigned int i = 0; i < m_compenents.size(); ++i)
        {
            auto &com = m_compenents[i];
            auto t = std::dynamic_pointer_cast<T>(com);
            if (t)
            {
                return t;
            }
        }
        return SharePtr<T>();
    }

    template <class T>
    inline void GameObject::removeComponent(SharePtr<T> component)
    {
        for (unsigned int i = 0; i < m_compenents.size(); ++i)
        {
            auto &com = m_compenents[i];
            if (component->getClassID() == com->getClassID())
            {
                m_compenents.erase(m_compenents.begin() + i);
            }
        }
    }
    template <class T>
    inline SharePtr<T> GameObject::addComponent(SharePtr<T> component)
    {
        if (component)
        {
            component->SetParent(m_GameObject.lock());
            removeComponent<T>(component);
            m_compenents.push_back(component);
            return component;
        }
        return SharePtr<T>();
    }

    template <class T>
    inline SharePtr<T> GameObject::addComponent(T *component)
    {
        SharePtr<T> t = SharePtr<T>(component);
        auto com = addComponent<T>(t);
        return com;
    }

}  // namespace GameEngine