#include "GameObject.h"
#include "ResourceManager.h"
GameObjectManager* GameObjectManager::s_Instance = NULL;

GameObjectManager& GetGameObjectManager()
{
	return *GameObjectManager::s_Instance;
}

void GameObject::addComponent(int classID, Component* component) {
	m_compenents.push_back(std::pair<int, Component* >(classID,component));
}

template<class T> inline
T* GameObject::getComponent(int classID) {
	Component* com;
	com = queryComponentImplementation(classID);
	return	static_cast<T*> (com);
}

Component* GameObject::queryComponentImplementation(int classID) {
	for (auto i = m_compenents.begin(); i!= m_compenents.end(); ++i)
	{
		if ((*i).first == classID)
			return (*i).second;
	}
	return NULL;
}

void GameObject::Renderer() {
	SpriteRenderer* renderer = getComponent<SpriteRenderer>(ClassIDType::CLASS_BaseRenderer);
	if(renderer){
		renderer->DrawSprite(*ResourceManager::GetTexture("G:/CPPGame/Game/Textures/awesomeface.png"),
			glm::vec3(200, 200,0), glm::vec3(300, 400,0), 45.0f, glm::vec3(1.0f, 1.0f, 1.0f));
	}
}