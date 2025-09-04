#pragma once

#ifndef GAME_HPP
#define GAME_HPP

#include <SDL2/SDL.h>

class Game {
private:
	SDL_Window* sdlWindow;
	SDL_Surface* sdlSurface;
	SDL_Event event;

	uint32_t cornflowerBlue;

	// Game state
	bool done;
	int clicks;

	void INIT();

public:
	Game();
};

#endif