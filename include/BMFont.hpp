#pragma once

#include <string>
#include <vector>
#include <Image.hpp>

class BMFont {
private:
	Image* imgData;

public:
	BMFont(std::string filename);  // constructor
	~BMFont();  // destructor
};