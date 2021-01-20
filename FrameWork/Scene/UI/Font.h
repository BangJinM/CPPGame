#pragma once

#include <string>

#include "Object.h"
#include "Config.h"
#include "Texture.h"

// #include <ft2build.h>
// #include FT_FREETYPE_H

GameEngineBegin 

struct FontInfo
{
	char32_t c;
	int size;
	int width;
	int height;
	int bearing_x;
	int bearing_y;
	int advance_x;
	int advance_y;
	unsigned int glyph_index;
};

class Font : public Object
{
private:
	// 	std::string m_Path;
	// 	FT_Face m_Face;

	// public:
	// 	Font();
	// 	~Font();

	// 	void setFace(FT_Face face);
	// 	void setPath(std::string path);

	// 	void getText();

	// 	static FT_Library GetFontTypeLib();
};

GameEngineEnd