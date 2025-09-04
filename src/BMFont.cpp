#include <filesystem>
#include <fstream>

#include <panic.hpp>
#include <strings.hpp>
#include "BMFont.hpp"

bool fileExists(const std::string& filename) {
  return std::filesystem::exists(filename);
}

int parseInt(const std::string& text) {
  try {
    return std::stoi(text);
  } catch (const std::invalid_argument& e) {
    return 0;
  }
}

BMFont::BMFont(const std::string& filename) {
  if (!fileExists(filename)) {
    panicHalt("Couldn't find " + filename + "!");
    return;
  }

  std::ifstream fontFile(filename);
  std::string line;
  std::vector<std::string> pairs, pair;
  std::string k, v;
  BMFontGlyph tempGlyph;

  // TODO: Implement the loader

  if (fontFile.is_open()) {
    while (std::getline(fontFile, line)) {
      pairs.clear();

      if (startsWith(line, "info")) {
        // printf("%s\n", line.c_str());
        pairs = split(line, " ");

        for (const auto& p: pairs) {
          pair = split(p, "=");
          
          if (pair.size() == 2) {
            k = pair.at(0); v = pair.at(1);
            if (k == "face") {
              face = replaceAll(v, "\"", "");
              printf("Font face: %s\n", face.c_str());
            }
          }
        }
      } else if (startsWith(line, "common")) {
        pairs = split(line, " ");

        for (const auto& p: pairs) {
          pair = split(p, "=");

          if (pair.size() == 2) {
            k = pair.at(0); v = pair.at(1);

            if (k == "lineHeight") {
              lineHeight = parseInt(v);
              printf("Line height: %d\n", lineHeight);
            }
          }
        }
      } else if (startsWith(line, "page")) {
        pairs = split(line, " ");

        for (const auto& p: pairs) {
          pair = split(p, "=");

          if (pair.size() == 2) {
            k = pair.at(0); v = pair.at(1);

            if (k == "file") {
              this->filename = replaceAll(v, "\"", "");
              printf("Filename: %s\n", this->filename.c_str());
            }
          }
        }
      } else if (startsWith(line, "char") && !startsWith(line, "chars")) {
        while (contains(line, "  "))
          line = replaceAll(line, "  ", " ");

        // printf("%s\n", line.c_str());

        // Parse the whole line, then copy the record
        memset(&tempGlyph, 0, sizeof(BMFontGlyph));
        pairs = split(line, " ");

        for (const auto& p: pairs) {
          pair = split(p, "=");

          if (pair.size() == 2) {
            k = pair.at(0); v = pair.at(1);

            if (k == "id") tempGlyph.id = parseInt(v);
            if (k == "x") tempGlyph.x = parseInt(v);
            if (k == "y") tempGlyph.y = parseInt(v);
            if (k == "width") tempGlyph.width = parseInt(v);
            if (k == "height") tempGlyph.height = parseInt(v);
            if (k == "xoffset") tempGlyph.xoffset = parseInt(v);
            if (k == "yoffset") tempGlyph.yoffset = parseInt(v);
            if (k == "xadvance") tempGlyph.xadvance = parseInt(v);
          }
        }

        glyphs.insert({ tempGlyph.id, &tempGlyph });
      }
    }
  }

  fontFile.close();

  if (image != nullptr) delete image;
  image = new Image(filename);
}

BMFont::~BMFont() {
  for (const auto& g: glyphs)
    delete g.second;

  glyphs.clear();

  delete image;
  image = nullptr;
}

int BMFont::getLineHeight() {
  return lineHeight;
}

Image *BMFont::getImage() {
	return image;
}

template <typename T, typename U>
bool mapHasKey(const std::map<T, U>& map, T key) {
  return map.count(key) > 0;
}

int BMFont::measure(const std::string& text) {
  int result = 0;
  int charcode;

  for (int a=0; a < text.length(); a++) {
    charcode = text.at(a);
    if (mapHasKey(glyphs, charcode))
      result += glyphs[charcode]->xadvance;
  }

  return result;
}

std::map<int, BMFontGlyph *> BMFont::getGlyphs() {
	return glyphs;
}

void printBMFont(
  BMFont font,
  const std::string& text,
  const int x, const int y,
  SDL_Surface* surface)
{
  int left = x;
  int charcode;
  BMFontGlyph* g = nullptr;
  SDL_Rect srcRect, destRect;

  for (int a=0; a < text.length(); a++) {
    charcode = text.at(a);
    if (!mapHasKey(font.getGlyphs(), charcode)) continue;

    g = font.getGlyphs()[charcode];
    srcRect = { g->x, g->y, g->width, g->height };
    destRect = { left + g->xoffset, y + g->yoffset, g->width, g->height };

    SDL_BlitSurface(font.getImage()->getSurface(), &srcRect, surface, &destRect);

    left += g->xadvance;
  }
}
