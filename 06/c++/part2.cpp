#include <cctype>
#include <cstddef>
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

struct Operand {
  char operand;
  std::size_t index;
};

int main() {
  const auto& lines = readFileToVector();
  std::uint64_t total = 0;

  std::vector<Operand> operands;
  std::vector<std::vector<std::uint64_t>> nums;
  std::string temp;

  for (std::size_t index = 0; index < lines[4].size(); ++index) {
    if (lines[4][index] != ' ') {
      operands.push_back({lines[4][index], index});
    }
  }

  for (const auto& operand : operands) {
    std::uint64_t sum = 0;

    for (std::size_t index = operand.index; index < lines[0].size(); ++index) {
      if ((lines[0][index] != ' ') ||
          (lines[1][index] != ' ') ||
          (lines[2][index] != ' ') ||
          (lines[3][index] != ' ')) {
        std::string tempString;
        tempString += lines[0][index];
        tempString += lines[1][index];
        tempString += lines[2][index];
        tempString += lines[3][index];

        std::uint64_t tempNum = std::stoull(tempString);

        if (sum == 0) {
          sum = tempNum;
        } else {
          if (operand.operand == '*') {
            sum *= tempNum;
          } else {
            sum += tempNum;
          }
        }
      } else {
        break;
      }
    }

    total += sum;
  }

  std::println("Grand total = {}", total);
}
