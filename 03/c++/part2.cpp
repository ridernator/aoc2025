#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <iostream>
#include <iterator>
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

int main() {
  const auto& lines = readFileToVector();

  std::uint64_t total = 0;

  for (const auto& line : lines) {
    auto lastIndex = line.begin() - 1;

    for (std::uint64_t index = 0; index < 12; ++index) {
      lastIndex = std::max_element(lastIndex + 1, line.end() - (11 - index));

      total += std::stoull(line.substr(std::distance(line.begin(), lastIndex), 1)) * std::pow(10, 11 - index);
    }
  }


  std::println("Output joltage = {}", total);
}
