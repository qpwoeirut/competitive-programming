#include "obstacles.h"
#include "obstacles.cpp"
#include <cassert>
#include <cstdio>
#include <random>

using namespace std;

void test() {
    mt19937 rng(8);
    for (int N = 1; N <= 10; ++N) {
        for (int M = 1; M <= 10; ++M) {
            cerr << "N M " << N << ' ' << M << endl;
            std::vector<int> T(N), H(M);
            for (int t=0; t<100000; ++t) {
                for (int i=0; i<N; ++i) T[i] = rng() % 20;
                for (int i=0; i<M; ++i) H[i] = rng() % 20;

                initialize(T, H);
                for (int q=0; q<100; ++q) {
                    int S = rng() % M;
                    int D = rng() % M;
                    bool res = can_reach(0, M - 1, S, D);
                    bool ans = brute(T, H, S, D);
                    if (res != ans) {
                        cout << N << ' ' << M << endl;
                        for (int i=0; i<N; ++i) cout << T[i] << ' ';
                        cout << endl;
                        for (int i=0; i<M; ++i) cout << H[i] << ' ';
                        cout << endl;
                        cout << S << ' ' << D << endl;

                        cout << res << ' ' << ans << endl;
                    }
                    assert(res == ans);
                }
            }
        }
    }
}

int main() {
    test(); return 0;
  int N, M;
  assert(2 == scanf("%d %d", &N, &M));
  std::vector<int> T(N), H(M);
  for (int i = 0; i < N; i++)
    assert(1 == scanf("%d", &T[i]));
  for (int i = 0; i < M; i++)
    assert(1 == scanf("%d", &H[i]));

  int Q;
  assert(1 == scanf("%d", &Q));
  std::vector<int> L(Q), R(Q), S(Q), D(Q);
  for (int i = 0; i < Q; i++)
    assert(4 == scanf("%d %d %d %d", &L[i], &R[i], &S[i], &D[i]));

  fclose(stdin);

  std::vector<bool> A(Q);

  initialize(T, H);

  for (int i = 0; i < Q; i++)
    A[i] = can_reach(L[i], R[i], S[i], D[i]);

  for (int i = 0; i < Q; i++)
    if (A[i])
      printf("1\n");
    else
      printf("0\n");
  fclose(stdout);

  return 0;
}
