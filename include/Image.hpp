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
	Image(std::string filename) {
		surface = IMG_Load(filename.c_str());

		if (surface == nullptr) {
			printf("Couldn't load %s!", filename.c_str());
			return;
		}
	}

	SDL_Surface* getSurface() { return surface; }
	bool isSet() { return surface != nullptr; }

	~Image() {
		SDL_FreeSurface(surface);
	}
};

#endif