#include <filesystem>
#include <fstream>

#include <panic.hpp>
#include "BMFont.hpp"

bool fileExists(std::string filename) {
	return std::filesystem::exists(filename);
}

bool startsWith(std::string txt, std::string searchStr) {
	return txt.rfind(searchStr) == 0;
}

std::vector<std::string> split(const std::string& text, const std::string& delimiter) {
	std::vector<std::string> result;
	std::string str;
	size_t pos;

	if (text.empty()) return result;

	str = text;
	pos = 0;

	while ((pos = str.find(delimiter)) != std::string::npos) {
		auto token = str.substr(0, pos);
		result.push_back(token);
		str.erase(0, pos + delimiter.length());
	}

	result.push_back(str);

	return result;
}

BMFont::BMFont(std::string filename) {
	if (!fileExists(filename)) {
		panicHalt("Couldn't find " + filename + "!");
		return;
	}

	std::ifstream fontFile(filename);
	std::string line;

	// TODO: Implement the loader

	if (fontFile.is_open()) {
		while (std::getline(fontFile, line)) {
			if (startsWith(line, "info")) {

			}
		}
	}
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