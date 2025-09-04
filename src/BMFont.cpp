#include <filesystem>
#include "BMFont.hpp"

bool fileExists(std::string filename) {
	return std::filesystem::exists(filename);
}

void panicHalt(std::string msg) {
	printf("%s\n", msg.c_str());
	exit(1);
}

BMFont::BMFont(std::string filename) {
	if (!fileExists(filename)) {
		panicHalt("Couldn't find " + filename + "!");
		return;
	}


}