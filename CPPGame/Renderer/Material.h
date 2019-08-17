#ifndef SRC_RENDERER_MATERIAL_H
#define SRC_RENDERER_MATERIAL_H
#include "Shader.h"
#include "Texture2D.h"

class Object;

class Material
{
public:
	Material(Object* camera);

	void Use(Object* gameObject);

	~Material();
	Object* m_Camera;
	Texture2D m_Texture;
	Shader m_Shader;
};

#endif