#include "GameObject.h"
#include "Camera.h"
#include "SpriteRendererMaterial.h"
#include "CubeRendererMaterial.h"
GameObjectManager* GameObjectManager::s_Instance = NULL;

GameObjectManager& GetGameObjectManager()
{
	return *GameObjectManager::s_Instance;
}

void Object::addComponent(int classID, Component* component) {
	//component->m_Host = this;
	m_compenents.push_back(std::pair<int, Component* >(classID,component));
}

template<class T> inline
T* Object::getComponent(int classID) {
	Component* com;
	com = queryComponentImplementation(classID);
	return	static_cast<T*> (com);
}

Component* Object::queryComponentImplementation(int classID) {
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
		if (nullptr == trans)
			return;
		auto texture = *ResourceManager::GetTexture("Resources/Textures/awesomeface.png");
		renderer->DrawSprite(
			texture,
			trans->getTransformMatrix4()
		);
		//上面写法和下面写法一致，但是下面写法莫名其妙的会盖面texture的内容
		//auto* trans = getComponent<Transform>(ClassIDType::CLASS_Transform);
		//renderer->DrawSprite(
		//	*ResourceManager::GetTexture("G:/CPPGame/Game/Textures/awesomeface.png"),
		//	trans->m_LocalPosition,
		//	trans->m_LocalScale,
		//	trans->m_LocalRotation
		//);
	}
}

void GameObject::RendererMaterial() {
	SpriteRendererMaterial* renderer = getComponent<SpriteRendererMaterial>(ClassIDType::CLASS_BaseRenderer);
	if (renderer) {
		auto* trans = getComponent<Transform>(ClassIDType::CLASS_Transform);
		if (nullptr == trans)
			return;
		auto texture = *ResourceManager::GetTexture("Resources/Textures/awesomeface.png");
		renderer->DrawSprite(
			this,
			texture,
			trans->getTransformMatrix4()
		);
		//上面写法和下面写法一致，但是下面写法莫名其妙的会盖面texture的内容
		//auto* trans = getComponent<Transform>(ClassIDType::CLASS_Transform);
		//renderer->DrawSprite(
		//	*ResourceManager::GetTexture("G:/CPPGame/Game/Textures/awesomeface.png"),
		//	trans->m_LocalPosition,
		//	trans->m_LocalScale,
		//	trans->m_LocalRotation
		//);
	}
}

void CubeObject::Renderer(Object* cameraObject)
{
	CubeRenderer* renderer = getComponent<CubeRenderer>(ClassIDType::CLASS_BaseRenderer);
	if (renderer) {
		auto* trans = getComponent<Transform>(ClassIDType::CLASS_Transform);
		if (nullptr == trans)
			return;
		auto texture = *ResourceManager::GetTexture("Resources/Textures/container.jpg");
		renderer->DrawSprite(
			texture,
			cameraObject->getComponent<Transform>(ClassID(Transform))->getTransformMatrix4(),
			cameraObject->getComponent<Camera>(ClassID(Camera))->getProjectionMatrix(),
			trans->getTransformMatrix4()
		);
	}
}


void CubeObject::RendererMaterial() {
	CubeRendererMaterial* renderer = getComponent<CubeRendererMaterial>(ClassIDType::CLASS_BaseRenderer);
	if (renderer) {
		renderer->DrawSprite(this);
	}
}