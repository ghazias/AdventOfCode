#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

const std::size_t NUMSLOPES{5};

int checkSlope(const std::vector<std::string>& slope, int fall, int run) {
  // count number of trees encountered
  std::size_t x{}, treeCount{}, lineSize{slope[0].size()};
  for (std::size_t i = 0; i < slope.size(); i += fall) {
    if (slope[i].at(x) == '#') {
      ++treeCount;
    }
    x = (x + run) % lineSize;
  }

  return treeCount;
}

int main(int, char* argv[]) {
  // store input line by line in vector
  std::ifstream input(argv[1]);
  std::vector<std::string> lines;
  std::string line{};
  while (std::getline(input, line)) {
    lines.push_back(line);
  }

  // count
  long result{1};
  int fall[NUMSLOPES]{1, 1, 1, 1, 2};
  int run[NUMSLOPES]{1, 3, 5, 7, 1};
  for (std::size_t i = 0; i < NUMSLOPES; ++i) {
    result *= checkSlope(lines, fall[i], run[i]);
  }

  std::cout << "Result = " << result << '\n';
}