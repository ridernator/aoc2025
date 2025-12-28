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

int main() {
  const auto& lines = readFileToVector();
  std::uint64_t total = 0;

  std::vector<char> operands;
  std::vector<std::vector<std::uint64_t>> nums;
  std::string temp;

  for (const auto& line : lines) {
    std::stringstream ss(line);

    if (line.find('*') == std::string::npos) {
      std::uint64_t index = 0;

      while (std::getline(ss, temp, ' ')) {
        if (temp[0] != 0) {
          if (nums.size() <= index) {
            nums.push_back({});
          }

          nums[index].push_back(std::stoull(temp));

          ++index;
        }
      }
    } else {
      while (std::getline(ss, temp, ' ')) {
        if (temp[0] != 0) {
          operands.push_back(temp[0]);
        }
      }
    }
  }

  for (std::size_t index = 0; index < operands.size(); ++index) {
    std::println("num1: {}, num2: {}, num3: {}, operand: {}", nums[index][0], nums[index][1], nums[index][2], operands[index]);
    std::uint64_t sum = nums[index][0];

    if (operands[index] == '*') {
      for (std::size_t index2 = 1; index2 < nums[index].size(); ++index2) {
        sum *= nums[index][index2];
      }
    } else {
      for (std::size_t index2 = 1; index2 < nums[index].size(); ++index2) {
        sum += nums[index][index2];
      }
    }

    total += sum;
  }

  std::println("Grand total = {}", total);
}
