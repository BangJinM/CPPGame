#include "GameObject.h"
#include "ResourceManager.h"
#include "Transform.h"
GameObjectManager* GameObjectManager::s_Instance = NULL;

GameObjectManager& GetGameObjectManager()
{
	return *GameObjectManager::s_Instance;
}

void GameObject::addComponent(int classID, Component* component) {
	//component->m_Host = this;
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
		auto* trans = getComponent<Transform>(ClassIDType::CLASS_Transform);
		auto texture = *ResourceManager::GetTexture("G:/CPPGame/Game/Textures/awesomeface.png");
		renderer->DrawSprite(
			texture,
			trans->m_LocalPosition,
			trans->m_LocalScale,
			trans->m_LocalRotation
		);
		//����д��������д��һ�£���������д��Ī������Ļ����texture������
		//auto* trans = getComponent<Transform>(ClassIDType::CLASS_Transform);
		//renderer->DrawSprite(
		//	*ResourceManager::GetTexture("G:/CPPGame/Game/Textures/awesomeface.png"),
		//	trans->m_LocalPosition,
		//	trans->m_LocalScale,
		//	trans->m_LocalRotation
		//);
	}
}