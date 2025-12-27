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

std::uint64_t countNeighbours(const std::vector<std::string> data,
                              const std::int64_t row,
                              const std::int64_t column) {
  std::uint64_t returnVal = 0;

  for (std::int64_t x = column - 1; x <= column + 1; ++x) {
    for (std::int64_t y = row - 1; y <= row + 1; ++y) {
      if ((x >= 0) && (x < (std::int64_t) data[0].size()) && (y >= 0) && (y < (std::int64_t) data.size())) {
        if (!((x == column) && (y == row))) {
          if (data[y][x] == '@') {
            ++returnVal;
          }
        }
      }
    }
  }

  return returnVal;
}

int main() {
  const auto& lines = readFileToVector();

  std::uint64_t total = 0;

  for (std::int64_t row = 0; row < (std::int64_t) lines.size(); ++row) {
    for (std::int64_t col = 0; col < (std::int64_t) lines[0].size(); ++col) {
      if (lines[row][col] == '@') {
        if (countNeighbours(lines, row, col) < 4) {
          ++total;
        }
      }
    }
  }

  std::println("Number of accessible rolls = {}", total);
}
