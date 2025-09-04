#pragma once

#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Image {
private:
	SDL_Surface* surface;

public:
	Image();
	Image(std::string filename);

	SDL_Surface* getSurface();
	bool isSet();

	~Image();
};

#endif