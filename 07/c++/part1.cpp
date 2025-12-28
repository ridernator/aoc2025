#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <iostream>
#include <print>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

#define INPUT "../data/input"

/**
 * Read a file entirely into a stringstream
 *
 * @param The name of the file to read
 * @return The contents of the file
 **/
std::stringstream readFile(const std::string& filename = INPUT) {
  std::ifstream fileStream(filename);
  std::stringstream returnVal;

  returnVal << fileStream.rdbuf();

  return returnVal;
}

/**
 * Read a file entirely into a vector of strings
 *
 * @param The name of the file to read
 * @return The vector of lines in the file
 **/
std::vector<std::string> readFileToVector(const std::string& filename = INPUT) {
  std::ifstream fileStream(filename);
  std::string string;
  std::vector<std::string> returnVal;

  while (std::getline(fileStream, string)) {
    returnVal.push_back(string);
  }

  return returnVal;
}

enum class HasPath {
  TRUE,
  FALSE,
  UNKNOWN
};

struct Splitter {
  std::uint64_t x;
  std::uint64_t y;
  HasPath hasPath = HasPath::UNKNOWN;
};

int main() {
  std::vector<Splitter> splitters;

  const auto& lines = readFileToVector();

  for (std::uint64_t y = 0; y < lines.size(); ++y) {
    for (std::uint64_t x = 0; x < lines[0].size(); ++x) {
      if (lines[y][x] == '^') {
        splitters.push_back({x, y});
      }
    }
  }

  splitters[0].hasPath = HasPath::TRUE;

  for (auto iterator = splitters.begin() + 1; iterator != splitters.end(); ++iterator) {
    auto& splitter = *iterator;

    for (std::uint64_t y = splitter.y - 1; y != 0; --y) {
      for (auto iterator2 = splitters.begin(); iterator2 != iterator; ++iterator2) {
        if (iterator2->y == y) {
          if (iterator2->x == splitter.x) {
            splitter.hasPath = HasPath::FALSE;

            break;
          } else if ((iterator2->x == splitter.x + 1) || (iterator2->x == splitter.x - 1)) {
            if (iterator2->hasPath == HasPath::TRUE) {
              splitter.hasPath = HasPath::TRUE;

              break;
            }
          }
        }
      }

      if (splitter.hasPath != HasPath::UNKNOWN) {
        break;
      }
    }
  }

  std::uint64_t splitCount = std::count_if(splitters.begin(), splitters.end(), [] (const auto& splitter) {
    return splitter.hasPath == HasPath::TRUE;
  });

  std::println("Number of times beam is split = {}", splitCount);
}
