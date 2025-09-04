#pragma once

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class VGA {
private:
	SDL_Window* sdlWindow = nullptr;
	SDL_Surface* sdlSurface = nullptr;

public:
	void initSDL();
	void initSurface();
	void freeSurface();

	SDL_Surface* getSurface() { return sdlSurface; }

	int getScreenWidth();
	int getScreenHeight();
	// default font line height
	int getLineHeight();

	void print(std::string text, int x, int y);

	void flush();
};
