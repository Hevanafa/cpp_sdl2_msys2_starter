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
  // sdlSurface = SDL_GetWindowSurface(sdlWindow);

  sdlVGAScaled = SDL_GetWindowSurface(sdlWindow);
  sdlVGASurface = SDL_CreateRGBSurfaceWithFormat(0, 320, 200, 32, sdlVGAScaled->format->format);
}

void VGA::initFont() {
  // defaultFont = new BMFont("assets\\fonts\\chikarego_regular_14.txt");
  defaultFont = new BMFont("assets\\fonts\\nokia_cellphone_fc_8.txt");
}

int VGA::getScreenWidth() {
  return sdlVGASurface->w;
}

int VGA::getScreenHeight() {
  return sdlVGASurface->h;
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

  defaultFont->print(text, x, y, sdlVGASurface);
}

void VGA::flush() {
  SDL_Rect destRect = {0, 0, 640, 400};
  SDL_BlitScaled(sdlVGASurface, nullptr, sdlVGAScaled, &destRect);
  SDL_UpdateWindowSurface(sdlWindow);
}

void VGA::freeFont() {
  delete defaultFont;
}

void VGA::freeSurface() {
  SDL_FreeSurface(sdlVGASurface);
  SDL_FreeSurface(sdlVGAScaled);
  SDL_DestroyWindow(sdlWindow);
}
