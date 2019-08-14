#ifndef SRC_RENDERER_BASE_RENDERER_H
#define SRC_RENDERER_BASE_RENDERER_H


#include "Component.h"
#include "ClassIDs.h"
#include "Shader.h"
class BaseRenderer:public Component
{
public:
	BaseRenderer(Shader* shader):Component(ClassID(BaseRenderer)){
		this->shader = *shader;
	}

	virtual void initRenderData() = 0;
protected:
	// Render state
	Shader shader;
	GLuint VAO,VBO;
};

#endif