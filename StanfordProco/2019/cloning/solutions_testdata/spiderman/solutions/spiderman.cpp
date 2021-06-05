#include <bits/stdc++.h>
#define FOR(i, n) for (int i = 0; i < (n); ++i)
#define ROF(i, n) for (int i = (n) - 1; i >= 0; --i)
#define REP(i, n) for (int i = 1; i <= (n); ++i)
#define REP3(i, s, n) for (int i = (s); i <= (n); ++i)
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int MAXN = 100001, MAXK = 100;
int N, K, A[MAXN], B[MAXN], dp[2][MAXN], dp_freq[MAXN];

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  cin >> N >> K;
  REP (i, N) cin >> A[i];

  copy(A, A + N, B);
  sort(B, B + N);
  int BN = unique(B, B + N) - B;
  REP (i, N) A[i] = lower_bound(B, B + BN, A[i]) - B;

  REP (k, K) {
    bool p = k & 1;
    int best_v = 0, prev_max = 0;
    fill(dp_freq, dp_freq + BN, 0);

    REP (i, N) {
      dp_freq[A[i]] = max(dp_freq[A[i]], prev_max);
      dp[p][i] = max(dp[p][i - 1], ++dp_freq[A[i]]);
      prev_max = max(prev_max, dp[!p][i]);
    }
  }

  cout << N - dp[K & 1][N] << endl;
  return 0;
}
