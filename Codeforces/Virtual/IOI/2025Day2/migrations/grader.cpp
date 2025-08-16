#include "migrations.h"
#include "migrations.cpp"
#include <cassert>
#include <cstdio>

int main() {
  int N;
  assert(1 == scanf("%d", &N));

  std::vector<int> P(N, 0);
  for (int i = 1; i < N; ++i) {
    assert(1 == scanf("%d", &P[i]));
  }

  std::vector<int> S(N, 0);
  for (int i = 1; i < N; ++i) {
    S[i] = send_message(N, i, P[i]);
  }
  for (int i = 1; i < N; ++i) {
    printf("%d%c", S[i], " \n"[i + 1 == N]);
  }

  auto [U, V] = longest_path(S);
  printf("%d %d\n", U, V);
  fclose(stdout);

  return 0;
}
