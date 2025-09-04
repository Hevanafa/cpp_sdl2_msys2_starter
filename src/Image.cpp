#include <Image.hpp>

Image::Image(): surface(nullptr) {}

Image::Image(std::string filename) {
	surface = IMG_Load(filename.c_str());

	if (surface == nullptr) {
		printf("Couldn't load %s!", filename.c_str());
		return;
	}
}

SDL_Surface* Image::getSurface() { return surface; }
bool Image::isSet() { return surface != nullptr; }

Image::~Image() {
	SDL_FreeSurface(surface);
}