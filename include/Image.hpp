#pragma once

#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Image {
private:
	SDL_Surface* surface;
	int w, h;

public:
	Image(std::string filename);  // constructor

	SDL_Surface* getSurface();
	bool isSet();
	int getWidth();
	int getHeight();

	~Image();  // destructor
};

#endif