#include <iostream>
#include <vector>

#include "utils.hpp"

int main() {
  const size_t N = 1 << 25;

  std::vector<float> A(N, 1);
  std::vector<float> B(N, 2);
  std::vector<float> C(N);

  struct timespec start, end;
  clock_gettime(CLOCK_MONOTONIC, &start);

  for (size_t i=0; i<N; ++i) {
    C[i] = A[i] * A[i] * B[i] - B[i] * B[i];
  }

  clock_gettime(CLOCK_MONOTONIC, &end);
  print_timediff("computation time: ", start, end);

  std::cout << "result: " << C[42] << std::endl;
}
