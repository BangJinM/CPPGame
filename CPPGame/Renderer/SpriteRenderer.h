#ifndef SRC_RENDERER_SPRITE_RENDERER_H
#define SRC_RENDERER_SPRITE_RENDERER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Texture2D.h"
#include "Shader.h"
#include "BaseRenderer.h"


class SpriteRenderer:public BaseRenderer
{
public:
	// Constructor (inits shaders/shapes)
	SpriteRenderer(Shader *shader);
	// Destructor
	~SpriteRenderer();
	// Renders a defined quad textured with given sprite
	void DrawSprite(Texture2D& texture, glm::mat4 modelMatrix4 = glm::mat4(1) , glm::vec3 color = glm::vec3(1.0f));

	// Initializes and configures the quad's buffer and vertex attributes
	void initRenderData() override;
};

#endif