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

int main() {
  const auto& fileData = readFile().str();
  std::string temp;
  std::vector<std::string> ranges;

  std::stringstream ss(fileData);
  while (std::getline(ss, temp, ',')) {
    ranges.push_back(temp);
  }

  std::uint64_t start;
  std::uint64_t stop;
  std::string numString;
  std::uint64_t sum = 0;

  for (const auto& range : ranges) {
    sscanf(range.c_str(), "%lu-%lu", &start, &stop);

    for (std::uint64_t num = start; num <= stop; ++num) {
      numString = std::to_string(num);

      if (numString.size() % 2 == 0) {
        if (numString.substr(0, numString.size() / 2).compare(numString.substr(numString.size() / 2)) == 0) {
          sum += num;
        }
      }
    }
  }

  std::println("Sum of invalid IDs = {}", sum);
}
