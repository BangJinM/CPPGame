#ifndef SRC_RENDERER_BASE_RENDERER_H
#define SRC_RENDERER_BASE_RENDERER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Texture2D.h"
#include "Shader.h"
#include "Component.h"
#include "ClassIDs.h"

class BaseRenderer:public Component
{
public:
	BaseRenderer():Component(ClassIDType::CLASS_BaseRenderer){}
};

#endif