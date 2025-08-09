#include "worldmap.h"
#include "worldmap.cpp"
#include <cassert>
#include <cstdio>

int main() {
  int T;
  assert(1 == scanf("%d", &T));

  std::vector<int> Nt(T), Mt(T);
  std::vector<std::pair<std::vector<int>, std::vector<int>>> AB;

  for (int t = 0; t < T; ++t) {
    assert(2 == scanf("%d %d", &Nt[t], &Mt[t]));

    int M = Mt[t];
    std::vector<int> A(M), B(M);

    for (int i = 0; i < Mt[t]; i++) {
      assert(2 == scanf("%d %d", &A[i], &B[i]));
    }
    AB.push_back(make_pair(A, B));
  }

  fclose(stdin);

  std::vector<std::vector<std::vector<int>>> Ct;

  for (int t = 0; t < T; t++) {
    int N = Nt[t], M = Mt[t];
    std::vector<int> A = AB[t].first, B = AB[t].second;

    auto C = create_map(N, M, A, B);
    Ct.push_back(C);
  }

  for (int t = 0; t < T; t++) {
    auto& C = Ct[t];
    int P = (int)C.size();

    std::vector<int> Q(P);
    for (int i = 0; i < P; ++i)
      Q[i] = (int)C[i].size();

    printf("%d\n", P);
    for (int i = 0; i < P; ++i)
      printf("%d%c", Q[i], " \n"[i + 1 == P]);
    printf("\n");
    for (int i = 0; i < P; i++) {
      for (int j = 0; j < Q[i]; j++) {
        printf("%d%c", C[i][j], " \n"[j + 1 == Q[i]]);
      }
    }
    if (t < T - 1)
      printf("\n");
  }

  fclose(stdout);

  return 0;
}
