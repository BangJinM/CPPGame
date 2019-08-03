#include "GameObject.h"

GameObjectManager* GameObjectManager::s_Instance = NULL;

GameObjectManager& GetGameObjectManager()
{
	return *GameObjectManager::s_Instance;
}

Component* GameObject::addComponent(int classID, Component* component) {
	m_compenents.push_back(std::pair<int, Component* >(classID,component));
}
template<class T> inline
Component* GameObject::getComponent(int classID) {
	Component* com;
	com = queryComponentImplementation(classID);
	return	*static_cast<T*> (com);
}

Component* GameObject::queryComponentImplementation(int classID) {
	for (auto i = m_compenents.begin(); i!= m_compenents.end(); ++i)
	{
		if ((*i).first == classID)
			return (*i).second;
	}
	return NULL;
}