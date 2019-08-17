#ifndef SRC_RENDERER_SPRITE_DEFAULT_MATERIAL_H
#define SRC_RENDERER_SPRITE_DEFAULT_MATERIAL_H
#include "Renderer/Shader.h"
#include "Renderer/Texture2D.h"

class Object;

class SpriteDefaultMaterial
{
public:
	SpriteDefaultMaterial(Object* camera);

	void Use(Object* gameObject);

	~SpriteDefaultMaterial();
	Object* m_Camera;
	Texture2D m_Texture;
	Shader m_Shader;
};

#endif