#include "../include/Game.hpp"

void Game::INIT() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		printf("Couldn't init SDL! Reason: %s\n", SDL_GetError());
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

	cornflowerBlue = SDL_MapRGB(sdlSurface->format, 0x64, 0x95, 0xed);
}

Game::Game(): done(false), clicks(0) {
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

		SDL_UpdateWindowSurface(sdlWindow);

		// Target 60 FPS
		SDL_Delay(16);
	}

	SDL_FreeSurface(sdlSurface);
	SDL_DestroyWindow(sdlWindow);
	SDL_Quit();
}
