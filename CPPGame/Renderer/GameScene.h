#ifndef SRC_RENDERER_SCENE_H
#define SRC_RENDERER_SCENE_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "GameObject.h"

class GameScene
{
public:
	// Constructor(s)
	GameScene();
	// Draw sprit
	virtual void Draw();

	void addChild(GameObject parent, GameObject* child);
	void deleteChild(GameObject parent, GameObject* child);
private:
};

#endif