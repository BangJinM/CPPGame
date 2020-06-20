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

    typedef std::list<BaseObject *> GameObjectArray;
    class BaseObject
    {

        friend class Component;

    public:
        template <class T>
        inline Component *getComponent();

        Component *addComponent(Component *component);

        void addChild(BaseObject *child);

        void getChildByName();

        void deleteChild(BaseObject *child);

        BaseObject();

        void setName(std::string name)
        {
            m_Name = name;
        }

    private:
        Component *getComponentBy(int classID);

    private:
        std::map<int, Component *> m_compenents;

        BaseObject *m_parent;

        GameObjectArray m_children;

        std::string m_Name;
    };

    class GameObject : BaseObject
    {
    public:
        GameObject();
        void draw();

    //private:
        bool m_isVisual = true;
        Transform *m_Transfrom;
        std::vector<Mesh*> m_Meshs;
        Material *m_Material;
    };

    template <class T>
    inline Component *BaseObject::getComponent()
    {
        auto itor = m_compenents.find(ClassID(T));
        if (itor != m_compenents.cend())
        {
            return static_cast<T *>(itor->second);
        }
        return nullptr;
    }
} // namespace GameEngine
#endif