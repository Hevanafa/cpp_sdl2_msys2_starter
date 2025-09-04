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

        // TODO: Parse the whole line, then copy the record
      }
    }
  }

  fontFile.close();

  if (imgData != nullptr) delete imgData;
  imgData = new Image(filename);
}

BMFont::~BMFont() {
  for (const auto& g: glyphs)
    delete g.second;

  glyphs.clear();

  delete imgData;
  imgData = nullptr;
}

int BMFont::getLineHeight() {
  return lineHeight;
}

// TODO: int measure(std::string text);
// TODO: void print(std::string text, int x, int y);
