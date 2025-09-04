#pragma once

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <Image.hpp>
#include <VGA.hpp>

class Game {
private:
	VGA vga;
	SDL_Event event;

	uint32_t cornflowerBlue;

	void loadImage(std::string filename, SDL_Surface* target);
	void spr(SDL_Surface* imgHandle, int x, int y);
	void freeImage(SDL_Surface* imgHandle);

	// Game assets
	Image* imgGasolineMaid = nullptr;

	// Game state
	bool done;
	int clicks;

	void INIT();
	void spr(Image* image, int x, int y);

public:
	Game();
};
