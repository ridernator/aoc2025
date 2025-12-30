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
#include <unordered_set>
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

struct Box {
  std::int64_t x;
  std::int64_t y;
  std::int64_t z;
};

struct Circuit {
  std::unordered_set<Box*> boxes;
};

struct Connection {
  Box* box1;
  Box* box2;
  double distance;
};

int main() {
  std::vector<Box*> boxes;
  std::vector<Connection*> connections;
  std::vector<Circuit*> circuits;

  const auto& lines = readFileToVector();

  for (const auto& line : lines) {
    Box* box = new Box();

    sscanf(line.c_str(), "%li,%li,%li", &box->x, &box->y, &box->z);

    boxes.push_back(box);

    Circuit* circuit = new Circuit();
    circuit->boxes.insert(box);
    circuits.push_back(circuit);
  }

  for (auto iterator = boxes.begin(); iterator != boxes.end(); ++iterator) {
    for (auto iterator2 = iterator + 1; iterator2 != boxes.end(); ++iterator2) {
      double distance = std::sqrt(std::pow(((*iterator)->x - (*iterator2)->x), 2) +
                                  std::pow(((*iterator)->y - (*iterator2)->y), 2) +
                                  std::pow(((*iterator)->z - (*iterator2)->z), 2));

      connections.push_back(new Connection{*iterator, *iterator2, distance});
    }
  }

  std::sort(connections.begin(), connections.end(), [] (const auto& a, const auto& b) {
    return (a->distance > b->distance);
  });

  std::int64_t lastX1 = 0;
  std::int64_t lastX2 = 0;

  while (circuits.size() != 1) {
    Connection* best = connections.back();

    for (const auto& circuit : circuits) {
      if (circuit->boxes.find(best->box1) != circuit->boxes.end()) {
        circuit->boxes.insert(best->box2);

        break;
      } else if (circuit->boxes.find(best->box2) != circuit->boxes.end()) {
        circuit->boxes.insert(best->box1);

        break;
      }
    }

    lastX1 = best->box1->x;
    lastX2 = best->box2->x;

    connections.pop_back();
    delete best;

    bool simplified = true;

    while (simplified) {
      simplified = false;

      for (auto iterator = circuits.begin(); iterator != circuits.end(); ++iterator) {
        for (const auto& box : (*iterator)->boxes) {
          for (auto iterator2 = iterator + 1; iterator2 != circuits.end(); ++iterator2) {
            if ((*iterator2)->boxes.find(box) != (*iterator2)->boxes.end()) {
              for (const auto& box2 : (*iterator2)->boxes) {
                (*iterator)->boxes.insert(box2);
              }

              delete *iterator2;
              circuits.erase(iterator2);

              simplified = true;

              break;
            }
          }
        }

        if (simplified) {
          break;
        }
      }
    }
  }

  std::println("Distance from wall = {}", (lastX1 * lastX2));

  for (const auto& connection : connections) {
    delete connection;
  }

  for (const auto& circuit : circuits) {
    delete circuit;
  }

  for (const auto& box : boxes) {
    delete box;
  }
}
