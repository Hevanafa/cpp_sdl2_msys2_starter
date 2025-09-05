#include "VGA.hpp"

void VGA::initSDL() {
  std::string s;

  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    s = SDL_GetError();
    panicHalt("Couldn't init SDL! Reason: " + s + "\n");
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

void VGA::initFont() {
  // defaultFont = new BMFont("assets\\fonts\\chikarego_regular_14.txt");
  defaultFont = new BMFont("assets\\fonts\\nokia_cellphone_fc_8.txt");
}

int VGA::getScreenWidth() {
  return sdlSurface->w;
}

int VGA::getScreenHeight() {
  return sdlSurface->h;
}

int VGA::getLineHeight() {
  return defaultFont->getLineHeight();
}

void VGA::print(std::string text, int x, int y) {
  int w, h;
  SDL_Color colour = {0xff, 0xff, 0xff, 0xff};
  SDL_Surface* tempSurface;
  SDL_Rect destRect;

  if (defaultFont == nullptr) return;

  printBMFont(*defaultFont, text, x, y, sdlSurface);
}

void VGA::flush() {
  SDL_UpdateWindowSurface(sdlWindow);
}

void VGA::freeFont() {
  delete defaultFont;
}

void VGA::freeSurface() {
  SDL_FreeSurface(sdlSurface);
  SDL_DestroyWindow(sdlWindow);
}
