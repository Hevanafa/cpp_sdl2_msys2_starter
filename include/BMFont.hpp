#pragma once

#include <string>
#include <vector>
#include <map>
#include <Image.hpp>

struct BMFontGlyph {
	int id, x, y;
	int width, height, xoffset, yoffset, xadvance;
	int lineHeight;
};

class BMFont {
private:
	std::string face;
	std::string filename;
	int lineHeight;
	std::map<int, BMFontGlyph> glyphs;
	Image* imgData = nullptr;

public:
	BMFont(std::string filename);  // constructor
	~BMFont();  // destructor
};