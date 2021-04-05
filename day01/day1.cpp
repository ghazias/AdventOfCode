#include <fstream>
#include <iostream>
#include <vector>

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cerr << "Format: " << argv[0] << " FILENAME\n";
    return 1;
  }

  std::fstream input(argv[1]);

  std::vector<int> nums;
  int n{};

  while (input >> n) {
    nums.push_back(n);
  }

  for (auto n : nums) {
    for (auto i : nums) {
      for (auto j : nums) {
        if (n + i + j == 2020) {
          std::cout << n << " + " << i << " + j "
                    << " = 2020\n " << n * i * j << "\n";
          return 0;
        }
      }
    }
  }
}
