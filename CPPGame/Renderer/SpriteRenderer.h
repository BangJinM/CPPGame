#ifndef SRC_RENDERER_SPRITE_RENDERER_MATERIAL_H
#define SRC_RENDERER_SPRITE_RENDERER_MATERIAL_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Texture2D.h"
#include "Shader.h"
#include "BaseRenderer.h"
#include "Material.h"

class SpriteRenderer :public BaseRenderer
{
public:
	// Constructor (inits shaders/shapes)
	SpriteRenderer(Shader *shader, Material* material);
	// Destructor
	~SpriteRenderer();
	// Renders a defined quad textured with given sprite
	void DrawSprite(Object* object);

	// Initializes and configures the quad's buffer and vertex attributes
	void initRenderData() override;

private:
	Material* material;
};

#endif