#include <Game.hpp>

void Game::INIT() {
  vga.initSDL();
  vga.initSurface();
  vga.initFont();

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
  SDL_BlitSurface(image->getSurface(), nullptr, vga.getSurface(), &destRect);
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

    SDL_FillRect(vga.getSurface(), NULL, cornflowerBlue);

    // Your drawing code here
    spr(imgGasolineMaid,
      (vga.getScreenWidth() - imgGasolineMaid->getWidth()) / 2,
      (vga.getScreenHeight() - imgGasolineMaid->getHeight()) / 2);

    vga.print("Esc - Exit", 0, vga.getScreenHeight() - vga.getLineHeight());

    vga.flush();

    // Target 60 FPS
    SDL_Delay(16);
  }

  // Cleanup code
  delete imgGasolineMaid;
  imgGasolineMaid = nullptr;

  vga.freeFont();
  vga.freeSurface();

  SDL_Quit();
}
