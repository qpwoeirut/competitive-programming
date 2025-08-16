#include "festival.h"
#include "festival.cpp"
#include <cassert>
#include <cstdio>

int main() {
  int N, A;
  assert(2 == scanf("%d %d", &N, &A));
  std::vector<int> P(N), T(N);
  for (int i = 0; i < N; i++)
    assert(2 == scanf("%d %d", &P[i], &T[i]));
  fclose(stdin);

  std::vector<int> R = max_coupons(A, P, T);

  int S = R.size();
  printf("%d\n", S);
  for (int i = 0; i < S; i++)
    printf("%s%d", (i == 0 ? "" : " "), R[i]);
  printf("\n");
  fclose(stdout);

  return 0;
}
