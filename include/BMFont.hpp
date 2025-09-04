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
	std::map<int, BMFontGlyph*> glyphs;
	Image* imgData = nullptr;

public:
	BMFont(const std::string& filename);  // constructor
	~BMFont();  // destructor

	int getLineHeight();
	int measure(const std::string& text);
};

void printBMFont(const std::string& text, const int x, const int y, const BMFont& font, const SDL_Surface& surface);
