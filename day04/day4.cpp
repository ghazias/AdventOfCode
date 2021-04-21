#include <algorithm>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

namespace {
bool is_field_valid(const std::string& name, const std::string& value) {
  std::cout << "field is " << name << ", value is " << value << '\n';
  if (name == "cid") {
    return true;
  }
  if (name == "byr") {
    int year = std::stoi(value);
    return 1920 <= year && year <= 2002;
  }
  if (name == "iyr") {
    int year = std::stoi(value);
    return 2010 <= year && year <= 2020;
  }
  if (name == "eyr") {
    int year = std::stoi(value);
    return 2020 <= year && year <= 2030;
  }
  if (name == "hgt") {
    std::istringstream val_stream(value);
    int height{};

    val_stream >> height;
    std::string unit{};
    std::getline(val_stream, unit);

    if (unit == "in") {
      return 59 <= height && height <= 76;
    }
    if (unit == "cm") {
      return 150 <= height && height <= 193;
    }

    return false;
  }
  if (name == "hcl") {
    return std::regex_match(value, std::regex("#[\\da-f]{6}"));
  }
  if (name == "ecl") {
    std::vector<std::string> valid_colors{"amb", "blu", "brn", "gry",
                                          "grn", "hzl", "oth"};
    return std::any_of(valid_colors.begin(), valid_colors.end(),
                       [&value](const auto& s) { return value == s; });
  }
  if (name == "pid") {
    return std::regex_match(value, std::regex("\\d{9}"));
  }

  return false;
}

bool is_valid(const std::string& line) {
  std::istringstream s{line};
  std::string field_name;
  std::string field_value;
  while (std::getline(s, field_name, ':') &&
         std::getline(s, field_value, ' ')) {
    if (!is_field_valid(field_name, field_value)) {
      return false;
    }
  }
  return true;
}

}  // namespace

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
    bool all_fields = std::all_of(
        valid_fields.begin(), valid_fields.end(),
        [&line](const auto& s) { return line.find(s) != std::string::npos; });
    bool valid = is_valid(line);
    if (all_fields && valid) {
      ++counter;
    }
  }

  std::cout << counter << " total valid passports\n";
}