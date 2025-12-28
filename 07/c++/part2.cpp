#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <iostream>
#include <print>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

#define INPUT "../data/inputSimple"

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

struct Splitter {
  std::uint64_t x;
  std::uint64_t y;
  std::vector<Splitter*> children = {};
  std::uint64_t count = 0;
};

std::uint64_t countLeaves(const Splitter* tree) {
  std::uint64_t count = 0;

  for (const auto& child : tree->children) {
    count += countLeaves(child);
  }

  count += (2 - tree->children.size());

  return count;
}

int main() {
  std::vector<Splitter*> splitters;

  const auto& lines = readFileToVector();

  for (std::uint64_t y = 0; y < lines.size(); ++y) {
    for (std::uint64_t x = 0; x < lines[0].size(); ++x) {
      if (lines[y][x] == '^') {
        splitters.push_back(new Splitter{x, y});
      }
    }
  }

  for (auto iterator = splitters.begin(); iterator != splitters.end(); ++iterator) {
    bool found = false;

    for (std::uint64_t y = (*iterator)->y; y < lines.size(); ++y) {
      for (auto iterator2 = iterator + 1; iterator2 != splitters.end(); ++iterator2) {
        if (((*iterator2)->y == y) && ((*iterator2)->x == (*iterator)->x - 1)) {
          (*iterator)->children.push_back(*iterator2);

          found = true;

          break;
        }
      }

      if (found) {
        break;
      }
    }

    found = false;

    for (std::uint64_t y = (*iterator)->y; y < lines.size(); ++y) {
      for (auto iterator2 = iterator + 1; iterator2 != splitters.end(); ++iterator2) {
        if (((*iterator2)->y == y) && ((*iterator2)->x == (*iterator)->x + 1)) {
          (*iterator)->children.push_back(*iterator2);

          found = true;

          break;
        }
      }

      if (found) {
        break;
      }
    }
  }

  for (auto iterator = splitters.rbegin(); iterator != splitters.rend(); ++iterator) {
    (*iterator)->count += (2 - (*iterator)->children.size());

    for (const auto& child : (*iterator)->children) {
      (*iterator)->count += child->count;
    }
  }

  std::println("Number of timelines = {}", splitters[0]->count);
}
