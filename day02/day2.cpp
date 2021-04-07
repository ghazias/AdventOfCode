#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace {
struct PasswordTest {
  std::size_t min;
  std::size_t max;
  char character;
  std::string password;

  bool isValid() const {
    std::size_t count{};
    if (password.at(min - 1) == character) {
      ++count;
    }
    
    if (password.at(max - 1) == character) {
      ++count;
    }

    return (count > 0 && count < 2);
  }
};

std::istream& operator>>(std::istream& in, PasswordTest& password_test) {
  in >> password_test.min;
  in.ignore(1);
  in >> password_test.max;
  in >> password_test.character;
  in.ignore(1);
  in >> password_test.password;
  return in;
}
}  // namespace

int main(int, char* argv[]) {
  std::ifstream input(argv[1]);
  std::string line{};
  PasswordTest test{};
  std::size_t validPasswords{};

  while (input >> test) {
    std::cout << "min: " << test.min << '\n'
              << "max: " << test.max << '\n'
              << "character: " << test.character << '\n'
              << "password: " << test.password << '\n';

    if (test.isValid()) {
      std::cout << "valid\n";
      ++validPasswords;
    }
  }

  std::cout << "-----------------------\n"
            << validPasswords << " passwords are valid\n";
}

// Day 1 Solution
/*
  bool isValid() const {
    std::size_t count{};
    for (std::size_t i = 0; i < password.size(); ++i) { // iterate through password n character times
      if (password.at(i) == character) { // check if char is relevant
        if (count >= max) { // ignore if we're past max num of char occurences
          return false;
        } else {
          ++count;
        }
      }
    }

    if (count < min) { return false; } // check if min occr

    return true;
  }
  */