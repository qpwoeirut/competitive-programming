#include "triples.h"
#include "triples.cpp"
#include <cassert>
#include <cstdio>

namespace {

void run_part1() {
  int N;
  assert(1 == scanf("%d", &N));
  std::vector<int> H(N);
  for (int i = 0; i < N; i++)
    assert(1 == scanf("%d", &H[i]));
  fclose(stdin);

  long long T = count_triples(H);

  printf("%lld\n", T);
  fclose(stdout);
}

void run_part2() {
  int M, K;
  assert(2 == scanf("%d %d", &M, &K));
  fclose(stdin);

  std::vector<int> H = construct_range(M, K);

  int N = H.size();
  printf("%d\n", N);
  for (int i = 0; i < N; i++)
    printf("%d%c", H[i], " \n"[i + 1 == N]);
  fclose(stdout);
}

} // namespace

int main() {
  int part;
  assert(1 == scanf("%d", &part));
  if (part == 1)
    run_part1();
  else if (part == 2)
    run_part2();
  return 0;
}
