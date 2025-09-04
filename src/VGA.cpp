#include "VGA.hpp"

void VGA::initSDL() {
	// printf("Hello world");
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		printf("Couldn't init SDL! Reason: %s\n", SDL_GetError());
		return;
	}

	if (TTF_Init() < 0) {
		printf("Couldn't init SDL_ttf! Reason: %s\n", TTF_GetError());
		return;
	}
}

void VGA::initSurface() {
	// Can return nullptr
	sdlWindow = SDL_CreateWindow(
		"Hello SDL2!",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		640, 400,
		SDL_WINDOW_SHOWN);

	// Can return nullptr
	sdlSurface = SDL_GetWindowSurface(sdlWindow);
}

void VGA::freeSurface() {
	SDL_FreeSurface(sdlSurface);
	SDL_DestroyWindow(sdlWindow);
}

void VGA::flush() {
	SDL_UpdateWindowSurface(sdlWindow);
}

int VGA::getScreenWidth() {
	return sdlSurface->w;
}

int VGA::getScreenHeight() {
	return sdlSurface->h;
}

int VGA::getLineHeight() {
	return TTF_FontLineSkip(nokiaFont);
}

void VGA::print(std::string text, int x, int y) {
	int w, h;
	SDL_Color colour = {0xff, 0xff, 0xff, 0xff};
	SDL_Surface* tempSurface;
	SDL_Rect destRect;

	TTF_SizeText(nokiaFont, text.c_str(), &w, &h);
	tempSurface = TTF_RenderText_Solid(nokiaFont, text.c_str(), colour);

	destRect = {x, y, w, h};
	SDL_BlitSurface(tempSurface, nullptr, sdlSurface, &destRect);

	SDL_FreeSurface(tempSurface);
}
