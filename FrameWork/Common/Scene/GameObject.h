#ifndef GameEngine_Common_Scene_Object_H
#define GameEngine_Common_Scene_Object_H

#include "ClassIDs.h"
#include <map>
#include <list>

namespace GameEngine
{
	class GameObject;
	typedef std::list<GameObject *> GameObjectArray;
    class GameObject
    {

        friend class Component;

    public:
        template <class T>
        inline Component *getComponent();

        Component *addComponent(Component *component);

        void addChild(GameObject *child);

        void getChildByName();

        void deleteChild(GameObject *child);

        GameObject();

    private:
        Component *getComponentBy(int classID);

    private:
        std::map<int, Component *> m_compenents;

        GameObject *m_parent;

        GameObjectArray m_children;

        std::string m_name;
    };
    template <class T>
    inline Component *GameObject::getComponent()
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