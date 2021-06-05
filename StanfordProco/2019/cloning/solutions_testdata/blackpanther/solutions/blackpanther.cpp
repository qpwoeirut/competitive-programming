#include <bits/stdc++.h>
#define FOR(i, n) for (int i = 0; i < (n); ++i)
#define ROF(i, n) for (int i = (n) - 1; i >= 0; --i)
#define REP(i, n) for (int i = 1; i <= (n); ++i)
#define REP3(i, s, n) for (int i = (s); i <= (n); ++i)
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

double best_val = -1e100;
int N, A[11];
char op[11];
bool used[11];

void dfs(int k, int x, double cur) {
  if (k == N - 1) {
    best_val = max(best_val, cur);
    return;
  }
  used[x] = true;
  FOR (i, N) if (!used[i]) {
    double v = cur;
    if (op[k] == '+') v += A[i];
    else if (op[k] == '-') v -= A[i];
    else if (op[k] == '*') v *= A[i];
    else if (op[k] == '/') v /= A[i];
    dfs(k + 1, i, v);
  }
  used[x] = false;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  cin >> N;
  FOR (i, N) cin >> A[i];
  FOR (i, N) cin >> op[i];
  FOR (i, N) dfs(0, i, A[i]);
  cout << fixed << setprecision(10);
  cout << best_val << endl;
  return 0;
}
