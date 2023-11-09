#include <cmath>
#include <cstdio>
#include <cstdlib>

auto main(const int argc, const char *const *const argv) noexcept -> int {
  if (argc != 3) {
    // return EXIT_FAILURE;
    return 1;
  }

  // atof is an unsafe function
  // really should use strtof and check error
  // const auto a = std::atof(argv[1]);
  // const auto b = std::atof(argv[2]);

  float a;
  float b;

  if (std::sscanf(argv[1], "%f", &a) != 1) {
    // return EXIT_FAILURE;
    return 1;
  }
  if (std::sscanf(argv[2], "%f", &b) != 1) {
    // return EXIT_FAILURE;
    return 1;
  }

  return std::fabs(a - b) > 0.1;
}
