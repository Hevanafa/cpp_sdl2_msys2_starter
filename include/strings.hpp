#pragma once

#include <string>
#include <vector>

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

bool contains(const std::string& source, const std::string& searchStr) {
  return source.find(searchStr) != std::string::npos;
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
