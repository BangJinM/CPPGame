#ifndef SRC_RENDERER_GAMEOBJECT_H
#define SRC_RENDERER_GAMEOBJECT_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <list>

#include "Node.h"
#include "ClassIDs.h"
#include "Component.h"

class GameObject;

typedef std::list<Node<GameObject> *> GameObjectList;
class GameObjectManager
{
public:
	GameObjectList m_ActiveNodes;

	static GameObjectManager* s_Instance;
};
GameObjectManager& GetGameObjectManager();

class Object
{
public:
	template<class T> inline
	T* getComponent(int classID);

	void addComponent(int id, Component* component);

private:
	Component* queryComponentImplementation(int classID);

private:
	typedef std::pair<int, Component*> ComponentPair;
	std::list<ComponentPair> m_compenents;
};

class GameObject :public Object {
public:
	void RendererMaterial();
};

class CubeObject :public Object
{
public:
	void Renderer(Object *cameraObject);
	void RendererMaterial();
};

template<class T> inline
T* Object::getComponent(int classID) {
	Component* com;
	com = queryComponentImplementation(classID);
	return	static_cast<T*> (com);
}

#endif