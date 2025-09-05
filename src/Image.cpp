#include <Image.hpp>

Image::Image(std::string filename) {
  surface = IMG_Load(filename.c_str());

  if (surface == nullptr)
    panicHalt("Couldn't load %s!", filename.c_str());
}

SDL_Surface* Image::getSurface() { return surface; }
bool Image::isSet() { return surface != nullptr; }

int Image::getWidth() {
  if (!isSet()) return 0;
  return surface->w;
}
int Image::getHeight() {
  if (!isSet()) return 0;
  return surface->h;
}

Image::~Image() {
  SDL_FreeSurface(surface);
}