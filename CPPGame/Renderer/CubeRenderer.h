#ifndef SRC_RENDERER_CUBE_RENDERER_MATERIAL_H
#define SRC_RENDERER_CUBE_RENDERER_MATERIAL_H

#include "Texture2D.h"
#include "BaseRenderer.h"
#include "Material.h"

class CubeRenderer :public BaseRenderer
{
public:
	CubeRenderer(Shader* shader,Material* material );

	void initRenderData();

	void DrawSprite(Object* object);

private:
	Material* m_Material;
};

#endif