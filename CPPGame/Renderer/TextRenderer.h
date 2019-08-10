#ifndef SRC_RENDERER_TEXT_RENDERER_H
#define SRC_RENDERER_TEXT_RENDERER_H

#include "BaseRenderer.h"

#include <ft2build.h>
#include FT_FREETYPE_H 
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <map>

#include "Shader.h"

struct Character {
	GLuint     TextureID;  // ���������ID
	glm::ivec2 Size;       // ���δ�С
	glm::ivec2 Bearing;    // �ӻ�׼�ߵ�������/������ƫ��ֵ
	GLuint     Advance;    // ԭ�����һ������ԭ��ľ���
};


/*
	�����������
*/
class TextTextureManager {
public:
	static TextTextureManager* getInstance();
	std::map<GLchar, Character> getCharacter();
private:
	TextTextureManager();
	std::map<GLchar, Character> Characters;
	static TextTextureManager* textTextureManagerInstance;
};


class TextRenderer :public BaseRenderer
{
public:
	TextRenderer();
	~TextRenderer();
	void DrawSprite(Shader &s, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
private:
	Shader shader;
	GLuint quadVAO,quaVBO;
	std::map<GLchar, Character> Characters;
	// Initializes and configures the quad's buffer and vertex attributes
	void initRenderData();
};

#endif