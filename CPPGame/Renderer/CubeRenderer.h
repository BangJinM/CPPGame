#ifndef SRC_RENDERER_CUBE_RENDERER_H
#define SRC_RENDERER_CUBE_RENDERER_H


#include "Texture2D.h"
#include "BaseRenderer.h"

class CubeRenderer :public BaseRenderer
{
public:
	CubeRenderer(Shader* shader);

	void initRenderData();

	void DrawSprite(Texture2D& texture, glm::mat4 cameraMatrix4, glm::mat4 projection, glm::mat4 model);

};

#endif