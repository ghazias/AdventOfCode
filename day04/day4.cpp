#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main(int, char* argv[]) {
  std::ifstream input{argv[1]};

  std::vector<std::string> lines;
  std::vector<std::string> valid_fields{"byr", "iyr", "eyr", "hgt",
                                        "hcl", "ecl", "pid"};
  int counter{};

  while (input) {
    std::string total;
    while (true) {
      std::string line;
      std::getline(input, line);
      if (line.empty()) {
        break;
      }
      if (!total.empty()) {
        total += ' ';
      }
      total += line;
    }
    lines.push_back(total);
  }

  for (const auto& line : lines) {
    // std::cout << line << "\n";
    bool valid = std::all_of(
        valid_fields.begin(), valid_fields.end(),
        [&line](const auto& s) { return line.find(s) != std::string::npos; });
    if (valid) {
      ++counter;
    }
  }

  std::cout << counter << " total valid passports\n";
}