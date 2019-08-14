#include "SpriteRenderer.h"


SpriteRenderer::SpriteRenderer(Shader* shader):BaseRenderer(shader){
	initRenderData();
}

SpriteRenderer::~SpriteRenderer()
{
	glDeleteVertexArrays(1, &this->VAO);
}


void SpriteRenderer::DrawSprite(Texture2D &texture, glm::mat4 modelMatrix4, glm::vec3 color)
{
	this->shader.Use();

	glm::vec2 imageSize = glm::vec2(texture.Width, texture.Height);

	modelMatrix4 = glm::scale(modelMatrix4, glm::vec3(imageSize.x, imageSize.y, 1.0f));

	this->shader.SetMatrix4("model", modelMatrix4);
	this->shader.SetVector3f("spriteColor", color);

	glActiveTexture(GL_TEXTURE0);
	texture.Bind();

	glBindVertexArray(this->VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}



void SpriteRenderer::initRenderData()
{
	GLfloat vertices[] = {
		// Pos      // Tex
		-0.5f, 0.5f, 0.0f, 1.0f,
		0.5f, -0.5f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f,

		-0.5f, 0.5f, 0.0f, 1.0f,
		0.5f,0.5f, 1.0f, 1.0f,
		0.5f, -0.5f, 1.0f, 0.0f
	};

	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(this->VAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}