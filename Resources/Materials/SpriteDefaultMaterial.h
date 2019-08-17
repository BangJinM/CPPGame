#ifndef SRC_RENDERER_SPRITE_DEFAULT_MATERIAL_H
#define SRC_RENDERER_SPRITE_DEFAULT_MATERIAL_H
#include "Renderer/Material.h"

class Camera;
class SpriteDefaultMaterial:public Material
{
public:
	SpriteDefaultMaterial(Object* camera);

	void Use(Object* gameObject) override;

	~SpriteDefaultMaterial()override;
	Object* m_Camera;
	Texture2D m_Texture;
	Shader m_Shader;
};

#endif