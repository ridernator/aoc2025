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

  std::vector<std::tuple<std::uint64_t, std::uint64_t>> ranges;

  for (const auto& line : lines) {
    if ((!line.empty()) && (line.find('-') != std::string::npos)) {
      std::uint64_t start;
      std::uint64_t end;

      sscanf(line.c_str(), "%lu-%lu", &start, &end);

      ranges.push_back({start, end});
    }
  }

  std::uint64_t total = 0;

  bool simplified = true;

  for (const auto& range : ranges) {
    std::println("start: {}, stop: {}", std::get<0>(range), std::get<1>(range));
  }
  std::println();

  while (simplified) {
    simplified = false;

    for (auto current = ranges.begin() + 1; current != ranges.end(); ++current) {
      for (auto previous = ranges.begin(); previous != current; ++previous) {
        if ((std::get<0>(*current) >= std::get<0>(*previous)) && (std::get<0>(*current) <= std::get<1>(*previous))) {
          std::get<1>(*previous) = std::max(std::get<1>(*previous), std::get<1>(*current));

          simplified = true;

          break;
        } else if ((std::get<1>(*current) >= std::get<0>(*previous)) && (std::get<1>(*current) <= std::get<1>(*previous))) {
          std::get<0>(*previous) = std::min(std::get<0>(*previous), std::get<0>(*current));

          simplified = true;

          break;
        } else if ((std::get<0>(*current) <= std::get<0>(*previous)) && (std::get<1>(*current) >= std::get<1>(*previous))) {
          std::get<0>(*previous) = std::min(std::get<0>(*previous), std::get<0>(*current));
          std::get<1>(*previous) = std::max(std::get<1>(*previous), std::get<1>(*current));

          simplified = true;

          break;
        }
      }

      if (simplified) {
        ranges.erase(current);

        for (const auto& range : ranges) {
          std::println("start: {}, stop: {}", std::get<0>(range), std::get<1>(range));
        }
        std::println();

        break;
      }
    }
  }

  for (const auto& range : ranges) {
    total += ((std::get<1>(range) - std::get<0>(range)) + 1);
  }

  std::println("Number of fresh ingredients = {}", total);
}
