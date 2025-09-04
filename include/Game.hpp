#pragma once

#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <Image.hpp>

class Game {
private:
	SDL_Window* sdlWindow;
	SDL_Surface* sdlSurface;
	SDL_Event event;

	TTF_Font* nokiaFont;

	uint32_t cornflowerBlue;

	// Helper functions
	int getScreenWidth();
	int getScreenHeight();

	void loadImage(std::string filename, SDL_Surface* target);
	void spr(SDL_Surface* imgHandle, int x, int y);
	void freeImage(SDL_Surface* imgHandle);

	// default font line height
	int getLineHeight();

	// Game assets
	Image* imgGasolineMaid = nullptr;

	// Game state
	bool done;
	int clicks;

	void INIT();
	void printString(std::string text, int x, int y);
	void spr(Image* image, int x, int y);

public:
	Game();
};

#endif