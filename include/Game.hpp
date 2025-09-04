#pragma once

#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class Game {
private:
	SDL_Window* sdlWindow;
	SDL_Surface* sdlSurface;
	SDL_Event event;

	TTF_Font* nokiaFont;

	uint32_t cornflowerBlue;

	// Game state
	bool done;
	int clicks;

	int getScreenWidth();
	int getScreenHeight();

	// default font line height
	int getLineHeight();

	void INIT();
	void printString(std::string text, int x, int y);

public:
	Game();
};

#endif