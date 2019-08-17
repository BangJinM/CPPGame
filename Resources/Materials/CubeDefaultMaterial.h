#ifndef SRC_RENDERER_CUBE_DEFAULT_MATERIAL_H
#define SRC_RENDERER_CUBE_DEFAULT_MATERIAL_H

#include "Renderer/Material.h"


class CubeDefaultMaterial :public Material
{
public:
	CubeDefaultMaterial(Object* camera);

	void Use(Object* gameObject) override;

	~CubeDefaultMaterial()override;
};

#endif