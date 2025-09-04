#include <Game.hpp>

void Game::INIT() {
	vga.initSDL();
	vga.initSurface();

	// Load game assets
	nokiaFont = TTF_OpenFont("fonts\\nokiafc22.ttf", 16);
	if (nokiaFont == nullptr) {
		printf("Couldn't load font! Reason: %s\n", TTF_GetError());
		return;
	}

	// Init game state
	cornflowerBlue = 0x6495ed; // SDL_MapRGB(sdlSurface->format, 0x64, 0x95, 0xed);
	done = false;
	clicks = 0;

	imgGasolineMaid = new Image("assets\\img\\gasoline_maid_256px.png");
}

void Game::spr(Image* image, int x, int y) {
	SDL_Rect destRect;
	if (image == nullptr) return;

	destRect = {x, y, image->getWidth(), image->getHeight()};
	SDL_BlitSurface(image->getSurface(), nullptr, sdlSurface, &destRect);
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
		spr(imgGasolineMaid,
			(getScreenWidth() - imgGasolineMaid->getWidth()) / 2,
			(getScreenHeight() - imgGasolineMaid->getHeight()) / 2);

		vga.print("Esc - Exit", 0, getScreenHeight() - getLineHeight());

		vga.flush();

		// Target 60 FPS
		SDL_Delay(16);
	}

	// Cleanup code
	delete imgGasolineMaid;
	imgGasolineMaid = nullptr;

	TTF_CloseFont(nokiaFont);
	TTF_Quit();

	vga.freeSurface();

	SDL_Quit();
}
