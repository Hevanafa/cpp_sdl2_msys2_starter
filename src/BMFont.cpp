#include <filesystem>
#include <fstream>

#include <panic.hpp>
#include "BMFont.hpp"

bool fileExists(const std::string& filename) {
  return std::filesystem::exists(filename);
}

bool startsWith(const std::string& txt, const std::string& searchStr) {
  return txt.rfind(searchStr) == 0;
}

std::vector<std::string> split(const std::string& text, const std::string& delimiter) {
  std::vector<std::string> result;
  std::string str = text;
  int pos = 0;

  if (text.empty()) return result;

  str = text;

  while ((pos = str.find(delimiter)) != std::string::npos) {
    auto token = str.substr(0, pos);
    result.push_back(token);
    str.erase(0, pos + delimiter.length());
  }

  result.push_back(str);

  return result;
}

std::string replaceAll(const std::string& source, const std::string& searchStr, const std::string& replaceStr) {
  std::string result = source;
  int pos = 0;
  
  if (searchStr.empty()) return result;

  while ((pos = result.find(searchStr, pos)) != std::string::npos) {
    result.replace(pos, searchStr.length(), replaceStr);
    pos += replaceStr.length();
  }

  return result;
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
      }
      // TODO: page
      // TODO: char
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