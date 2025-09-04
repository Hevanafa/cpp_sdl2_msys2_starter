#pragma once

#include <string>
#include <vector>
#include <map>
#include <SDL2/SDL.h>

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
	Image* image = nullptr;

public:
	BMFont(const std::string& filename);  // constructor
	~BMFont();  // destructor

	int getLineHeight();
	std::map<int, BMFontGlyph*> getGlyphs();
	int measure(const std::string& text);
};

void printBMFont(const std::string& text, const int x, const int y, const BMFont& font, const SDL_Surface& surface);
