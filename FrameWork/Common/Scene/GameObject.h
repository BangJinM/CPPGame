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
    class GameObject;
    class MeshDatas;
    class Material;

    class GameObject :public Object
    {

        friend class Component;

    public:
        template <class T>
        inline T *getComponent();

        void addComponent(Component *component);

        void addChild(GameObject *child);

        GameObject *getChildByName(std::string name);

        void deleteChild(GameObject *child);

        void setParent(GameObject *parent)
        {
            m_Parent = parent;
        }

        GameObject *getParent()
        {
            return m_Parent;
        }

        GameObject();
        virtual ~GameObject();

        void setName(std::string name)
        {
            m_Name = name;
        }

        std::string getName() {
            return m_Name;
        }

        std::map<std::string, GameObject *> getChildren()
        {
            return m_children;
        }

    private:
        Component *getComponentBy(int classID);

    private:
        std::map<int, Component *> m_compenents;

        GameObject *m_Parent;

        std::map<std::string, GameObject *> m_children;

        std::string m_Name;
    public:
        void Draw(GlmMat4 viewMat, GlmMat4 projectMat);

        //private:
        bool m_isVisual = true;
        std::vector<Mesh *> m_Meshs;
        std::vector<Material *> m_Materials;
    };

    template <class T>
    inline T *GameObject::getComponent()
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