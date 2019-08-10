#ifndef SRC_RENDERER_TEXT_RENDERER_H
#define SRC_RENDERER_TEXT_RENDERER_H

#include "BaseRenderer.h"
#include <ft2build.h>
#include FT_FREETYPE_H 

#include <map>
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
	Character getCharacter();
private:
	TextTextureManager();
	std::map<GLchar, Character> Characters;
	static TextTextureManager* textTextureManagerInstance;
};


class TextRenderer :public BaseRenderer
{
public:
	TextRenderer(Shader* shader);
	~TextRenderer();
	void DrawSprite(Shader &s, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
private:
	Shader shader;
	GLuint quadVAO;
	// Initializes and configures the quad's buffer and vertex attributes
	void initRenderData();
};

#endif