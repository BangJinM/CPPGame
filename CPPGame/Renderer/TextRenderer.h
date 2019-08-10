#ifndef SRC_RENDERER_TEXT_RENDERER_H
#define SRC_RENDERER_TEXT_RENDERER_H

#include "BaseRenderer.h"
#include <ft2build.h>
#include FT_FREETYPE_H 

#include <map>
struct Character {
	GLuint     TextureID;  // 字形纹理的ID
	glm::ivec2 Size;       // 字形大小
	glm::ivec2 Bearing;    // 从基准线到字形左部/顶部的偏移值
	GLuint     Advance;    // 原点距下一个字形原点的距离
};


/*
	字体纹理管理
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