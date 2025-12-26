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
  const auto& lines = readFileToVector();

  std::int32_t number = 50;
  std::uint32_t password = 0;

  char direction;
  std::uint32_t count;

  for (const auto& line : lines) {
    sscanf(line.c_str(), "%c%u", &direction, &count);

    if (direction == 'R') {
      number += count;

      while (number > 99) {
        number -= 100;
      }
    } else {
      number -= count;

      while (number < 0) {
        number += 100;
      }
    }

    if (number == 0) {
      ++password;
    }
  }

  std::println("Password = {}", password);
}
