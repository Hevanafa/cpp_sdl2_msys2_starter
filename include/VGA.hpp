#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class VGA {
private:
	SDL_Window* sdlWindow;
	SDL_Surface* sdlSurface;

public:
	void initSDL();
	void initSurface();
	void freeSurface();

	int getScreenWidth();
	int getScreenHeight();
	// default font line height
	int getLineHeight();

	void flush();
};
