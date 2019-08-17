#include "GameObject.h"
#include "SpriteRenderer.h"
#include "CubeRenderer.h"

GameObjectManager* GameObjectManager::s_Instance = NULL;

GameObjectManager& GetGameObjectManager()
{
	return *GameObjectManager::s_Instance;
}

void Object::addComponent(int classID, Component* component) {
	//component->m_Host = this;
	m_compenents.push_back(std::pair<int, Component* >(classID,component));
}



Component* Object::queryComponentImplementation(int classID) {
	for (auto i = m_compenents.begin(); i!= m_compenents.end(); ++i)
	{
		if ((*i).first == classID)
			return (*i).second;
	}
	return NULL;
}

void GameObject::RendererMaterial() {
	SpriteRenderer* renderer = getComponent<SpriteRenderer>(ClassIDType::CLASS_BaseRenderer);
	if (renderer) {
		renderer->DrawSprite(this);
	}
}

void CubeObject::RendererMaterial() {
	CubeRenderer* renderer = getComponent<CubeRenderer>(ClassIDType::CLASS_BaseRenderer);
	if (renderer) {
		renderer->DrawSprite(this);
	}
}