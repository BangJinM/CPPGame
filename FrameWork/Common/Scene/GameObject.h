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

    class GameObject :public Object
    {
        friend class Component;

    public:
        template <class T>
        inline T *getComponent();

        void addComponent(Component *component);

        void addChild(GameObject *child);
        void deleteChild(GameObject *child);
        void setParent(GameObject *parent);
        void setName(std::string name);
        void Draw(GlmMat4 viewMat, GlmMat4 projectMat);

        Component *getComponentBy(int classID);

        GameObject *getChildByName(std::string name);
        GameObject *getParent();

        GameObject();
        virtual ~GameObject();

        std::string getName() {
            return m_Name;
        }

        std::map<std::string, GameObject *> getChildren()
        {
            return m_children;
        }

    private:
        std::map<int, Component *> m_compenents;
        GameObject *m_Parent;
        std::map<std::string, GameObject *> m_children;
        std::string m_Name;
    public:
        //private:
        bool m_isVisual = true;
        std::shared_ptr<Mesh> m_Mesh;
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