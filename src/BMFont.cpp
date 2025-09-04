#include <filesystem>
#include <panic.hpp>
#include "BMFont.hpp"

bool fileExists(std::string filename) {
	return std::filesystem::exists(filename);
}

BMFont::BMFont(std::string filename) {
	if (!fileExists(filename)) {
		panicHalt("Couldn't find " + filename + "!");
		return;
	}

	// TODO: Implement the loader


}

BMFont::~BMFont() {
	for (const auto& g: glyphs)
		delete g.second;

	glyphs.clear();

	delete imgData;
	imgData = nullptr;
}

int BMFont::getLineHeight() {
	return lineHeight;
}