#pragma once

#include <string>
#include <SDL2/SDL.h>
#include <BMFont.hpp>

#include <panic.hpp>

class VGA {
private:
  SDL_Window* sdlWindow = nullptr;
  SDL_Surface* sdlVGASurface = nullptr;
  SDL_Surface* sdlVGAScaled = nullptr;


  BMFont* defaultFont = nullptr;

public:
  void initSDL();
  void initSurface();
  void initFont();

  SDL_Surface* getSurface() { return sdlVGASurface; }

  int getScreenWidth();
  int getScreenHeight();
  // default font line height
  int getLineHeight();

  void print(std::string text, int x, int y);

  void flush();
  void freeFont();
  void freeSurface();
};
