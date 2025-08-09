#include "souvenirs.h"
#include "souvenirs.cpp"
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <utility>
#include <vector>

namespace {
const int CALLS_CNT_LIMIT = 10'000;

int calls_cnt;
int N;
std::vector<long long> P;
std::vector<int> Q;

void quit(const char* message) {
  printf("%s\n", message);
  exit(0);
}
} // namespace

std::pair<std::vector<int>, long long> transaction(long long M) {
  calls_cnt++;
  if (calls_cnt > CALLS_CNT_LIMIT) {
    cout << N << endl;
    for (int x: P) cout << x << ' ';
    cout << endl;

    quit("Too many calls");
  }
  if (M >= P[0] || M < P[N - 1])
    quit("Invalid argument");

  std::vector<int> L;
  long long R = M;
  for (int i = 0; i < N; i++) {
    if (R >= P[i]) {
      R -= P[i];
      Q[i]++;
      L.push_back(i);
    }
  }
  return {L, R};
}

using namespace std;
void test() {
    mt19937_64 rng(8);

    for (N = 3; N <= 3; ++N) {
        for (int t=0; t<10000000; ++t) {
            P.resize(N);
            while (true) {
                for (int i=0; i<N; ++i) {
                    P[i] = rng() % 1'000'000LL;
                }
                sort(P.rbegin(), P.rend());
                bool ok = true;
                for (int i=1; i<N; ++i) ok &= P[i-1] != P[i];
                if (ok) break;
            }
            
            Q.assign(N, 0);
            calls_cnt = 0;
            buy_souvenirs(N, P[0]);

            for (int i=0; i<N; ++i) {
                if (Q[i] != i) {
                    cout << N << endl;
                    for (int x: P) cout << x << ' ';
                    cout << endl;
                    assert(0);
                }
            }
        }
    }
}

int main() {
    test(); return 0;
  assert(1 == scanf("%d", &N));
  P.resize(N);
  for (int i = 0; i < N; i++)
    assert(1 == scanf("%lld", &P[i]));
  fclose(stdin);

  Q.assign(N, 0);
  calls_cnt = 0;
  buy_souvenirs(N, P[0]);
  for (int i = 0; i < N; i++)
    printf("%s%d", i ? " " : "", Q[i]);
  printf("\n");
  fclose(stdout);

  return 0;
}
