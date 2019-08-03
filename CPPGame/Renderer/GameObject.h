#ifndef SRC_RENDERER_GAMEOBJECT_H
#define SRC_RENDERER_GAMEOBJECT_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <list>

#include "Texture2D.h"
#include "SpriteRenderer.h"
#include "Component.h"
#include "Node.h"
#include "ClassIDs.h"

//class GameObject
//{
//public:
//	// Object state
//	glm::vec2   Position, Size, Velocity;
//	glm::vec3   Color;
//	GLfloat     Rotation;
//	GLboolean   IsSolid;
//	GLboolean   Destroyed;
//	// Render state
//	Texture2D   Sprite;
//	// Constructor(s)
//	GameObject();
//	GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));
//	// Draw sprite
//	virtual void Draw(SpriteRenderer &renderer);
//};
class GameObject;

typedef std::list<Node<GameObject> *> GameObjectList;
class GameObjectManager
{
public:
	GameObjectList m_ActiveNodes;

	static GameObjectManager* s_Instance;
};
GameObjectManager& GetGameObjectManager();

class GameObject
{
public:
	template<class T> inline
	T* getComponent(int classID);
	void addComponent(int id, Component* component);

	void Renderer();

private:
	Component* queryComponentImplementation(int classID);

private:
	typedef std::pair<int, Component*> ComponentPair;
	std::list<ComponentPair> m_compenents;
};

#endif