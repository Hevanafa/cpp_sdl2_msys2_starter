#include "../include/Game.hpp"

void Game::INIT() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		printf("Couldn't init SDL! Reason: %s\n", SDL_GetError());
		return;
	}

	if (TTF_Init() < 0) {
		printf("Couldn't init SDL_ttf! Reason: %s\n", TTF_GetError());
		return;
	}

	// Can return nullptr
	sdlWindow = SDL_CreateWindow(
		"Hello SDL2!",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		640, 400,
		SDL_WINDOW_SHOWN);

	// Can return nullptr
	sdlSurface = SDL_GetWindowSurface(sdlWindow);

	// Load game assets
	nokiaFont = TTF_OpenFont("fonts\\nokiafc22.ttf", 14);
	if (nokiaFont == nullptr) {
		printf("Couldn't load font! Reason: %s\n", TTF_GetError());
		return;
	}

	// Init game state
	cornflowerBlue = SDL_MapRGB(sdlSurface->format, 0x64, 0x95, 0xed);
	done = false;
	clicks = 0;
}

int Game::getScreenWidth() {
	return sdlSurface->w;
}

int Game::getScreenHeight() {
	return sdlSurface->h;
}

int Game::getLineHeight() {
	return TTF_FontLineSkip(nokiaFont);
}

void Game::printString(std::string text, int x, int y) {
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

Game::Game() {
	INIT();

	while (!done) {
		// Handle inputs
		while (SDL_PollEvent(&event)) {
			switch(event.type) {
				case SDL_QUIT:
					done = true;
					break;

				case SDL_KEYDOWN:
					switch(event.key.keysym.sym) {
						case SDLK_ESCAPE:
							done = true;
					}
					break;
			}
		}

		SDL_FillRect(sdlSurface, NULL, cornflowerBlue);

		// Your drawing code here
		printString("Esc - Exit", 0, getScreenHeight() - getLineHeight());

		SDL_UpdateWindowSurface(sdlWindow);

		// Target 60 FPS
		SDL_Delay(16);
	}

	// Cleanup code
	TTF_CloseFont(nokiaFont);
	TTF_Quit();

	SDL_FreeSurface(sdlSurface);
	SDL_DestroyWindow(sdlWindow);
	SDL_Quit();
}
