#include <iostream>

#include <mpi.h>
#include <unistd.h>

auto main(int argc, char **argv) noexcept -> int {
  // initialize mpi
  MPI_Init(&argc, &argv);

  int rank;
  int size;

  // get rank of current process
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  // get total number of processes
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  static constexpr auto SIZE = 256;
  char hostname[SIZE];
  // get name of current machine
  gethostname(hostname, SIZE);

  std::cout << "I am process " << rank << " out of " << size
            << ". I am running on machine " << hostname << '\n';

  MPI_Finalize();
}
