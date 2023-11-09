#include <chrono>
#include <cmath>
#include <cstdlib>
#include <iostream>

#include <mpi.h>

#ifdef __cplusplus
extern "C" {
#endif

float f1(float x, int intensity);
float f2(float x, int intensity);
float f3(float x, int intensity);
float f4(float x, int intensity);

#ifdef __cplusplus
}
#endif

auto main(int argc, char **argv) noexcept -> int {
  if (argc < 6) {
    std::cerr << "usage: " << argv[0]
              << " <function_id> <a> <b> <n> <intensity>\n";
    // return EXIT_FAILURE;
    return -1;
  }

  const auto function_id = atoi(argv[1]);
  const auto a = atof(argv[2]);
  const auto b = atof(argv[3]);
  const auto n = atoi(argv[4]);
  const auto intensity = atoi(argv[5]);

  const auto dx = double{(b - a) / n};

  MPI_Init(&argc, &argv);

  int rank;
  int size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  const auto local_n = n / size;
  const auto extra = n % size;

  // distribute remaining work among processes
  const auto start = rank * local_n + (rank < extra ? rank : extra);
  const auto end = start + local_n + (rank < extra);

  auto local_result = 0.0;

  for (auto i = start; i < end; ++i) {
    const auto x = dx * i + a;
    auto result = 0.0;

    switch (function_id) {
    case 1:
      result = f1(x, intensity);
      break;
    case 2:
      result = f2(x, intensity);
      break;
    case 3:
      result = f3(x, intensity);
      break;
    case 4:
      result = f4(x, intensity);
      break;
    default:
      break;
    }

    local_result += result;
  }

  // sum up local results on rank 0
  auto total_result = 0.0;
  MPI_Reduce(&local_result, &total_result, 1, MPI_DOUBLE, MPI_SUM, 0,
             MPI_COMM_WORLD);

  if (rank == 0) {
    // print final result on rank 0
    std::cout << "Result: " << total_result * dx << '\n';
  }

  MPI_Finalize();
}
