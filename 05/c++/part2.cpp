#include <cstdint>
#include <cstdio>
#include <iostream>
#include <print>
#include <string>
#include <sstream>
#include <fstream>
#include <tuple>
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
  const auto lines = readFileToVector();

  std::uint64_t total = 0;
  std::vector<std::tuple<std::uint64_t, std::uint64_t>> ranges;

  for (const auto& line : lines) {
    if ((!line.empty()) && (line.find('-') != std::string::npos)) {
      std::uint64_t start;
      std::uint64_t end;

      sscanf(line.c_str(), "%lu-%lu", &start, &end);

      ranges.push_back({start, end});
    }
  }

  for (const auto& line : lines) {
    if ((!line.empty()) && (line.find('-') == std::string::npos)) {
      std::uint64_t num = std::stoul(line);
      for (const auto& range : ranges) {
        std::println("num: {}, min: {}, max: {}", num, std::get<0>(range), std::get<1>(range));
        if ((num >= std::get<0>(range)) && (num <= std::get<1>(range))) {
          ++total;

          break;
        }
      }
    }
  }

  std::println("Number of fresh ingredients = {}", total);
}
