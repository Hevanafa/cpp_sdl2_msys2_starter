#include "VGA.hpp"

void VGA::initSDL() {
	// printf("Hello world");
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		panicHalt("Couldn't init SDL! Reason: %s\n", SDL_GetError());
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

void VGA::initFont() {
	// defaultFont = new BMFont("assets\\fonts\\chikarego_regular_14.txt");
	defaultFont = new BMFont("assets\\fonts\\nokia_cellphone_fc_8.txt");

	// TODO: Make the 8x8 font
	// TODO: Load the 8x8 font

	// if (TTF_Init() < 0) {
	// 	printf("Couldn't init SDL_ttf! Reason: %s\n", TTF_GetError());
	// 	return;
	// }

	// // Load game assets
	// nokiaFont = TTF_OpenFont("assets\\fonts\\nokiafc22.ttf", 16);
	// if (nokiaFont == nullptr) {
	// 	printf("Couldn't load font! Reason: %s\n", TTF_GetError());
	// 	return;
	// }
}

int VGA::getScreenWidth() {
	return sdlSurface->w;
}

int VGA::getScreenHeight() {
	return sdlSurface->h;
}

int VGA::getLineHeight() {
	return 0;
	// if (nokiaFont == nullptr) return 0;

	// return TTF_FontLineSkip(nokiaFont);
}

void VGA::print(std::string text, int x, int y) {
	int w, h;
	SDL_Color colour = {0xff, 0xff, 0xff, 0xff};
	SDL_Surface* tempSurface;
	SDL_Rect destRect;

	if (defaultFont == nullptr) return;

	printBMFont(*defaultFont, text, x, y, sdlSurface);

	// if (nokiaFont == nullptr) return;

	// TTF_SizeText(nokiaFont, text.c_str(), &w, &h);
	// tempSurface = TTF_RenderText_Solid(nokiaFont, text.c_str(), colour);

	// destRect = {x, y, w, h};
	// SDL_BlitSurface(tempSurface, nullptr, sdlSurface, &destRect);

	// SDL_FreeSurface(tempSurface);
}

void VGA::flush() {
	SDL_UpdateWindowSurface(sdlWindow);
}

void VGA::freeFont() {
	delete defaultFont;
	// TTF_CloseFont(nokiaFont);
	// TTF_Quit();
}

void VGA::freeSurface() {
	SDL_FreeSurface(sdlSurface);
	SDL_DestroyWindow(sdlWindow);
}
