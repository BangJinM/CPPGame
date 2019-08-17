#ifndef SRC_RENDERER_SPRITE_RENDERER_MATERIAL_H
#define SRC_RENDERER_SPRITE_RENDERER_MATERIAL_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Texture2D.h"
#include "Shader.h"
#include "BaseRenderer.h"
#include "Material.h"

class SpriteRendererMaterial :public BaseRenderer
{
public:
	// Constructor (inits shaders/shapes)
	SpriteRendererMaterial(Shader *shader, Material* material);
	// Destructor
	~SpriteRendererMaterial();
	// Renders a defined quad textured with given sprite
	void DrawSprite(Object* object, Texture2D& texture, glm::mat4 modelMatrix4 = glm::mat4(1) , glm::vec3 color = glm::vec3(1.0f));

	// Initializes and configures the quad's buffer and vertex attributes
	void initRenderData() override;

private:
	Material* material;
};

#endif