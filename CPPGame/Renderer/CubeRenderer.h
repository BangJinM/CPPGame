#ifndef SRC_RENDERER_CUBE_RENDERER_H
#define SRC_RENDERER_CUBE_RENDERER_H


#include "BaseRenderer.h"

class CubeRenderer :public BaseRenderer
{
	CubeRenderer(Shader* shader);

	void initRenderData() override;
};

#endif