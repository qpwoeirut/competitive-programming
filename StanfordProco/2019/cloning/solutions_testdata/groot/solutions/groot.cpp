#include <bits/stdc++.h>
#define FOR(i, n) for (int i = 0; i < (n); ++i)
#define ROF(i, n) for (int i = (n) - 1; i >= 0; --i)
#define REP(i, n) for (int i = 1; i <= (n); ++i)
#define REP3(i, s, n) for (int i = (s); i <= (n); ++i)
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const char *OPS = "FBLR", *DIRS = "NWSE";
const int DIR_DELTA[4][2] = {{0, 1}, {-1, 0}, {0, -1}, {1, 0}};
int N, X, Y, D;
char DC;
string A;

pair<pii, int> simulate() {
  int x = 0, y = 0, d = 0;
  for (auto op : A) {
    if (op == 'F') {
      x += DIR_DELTA[d][0];
      y += DIR_DELTA[d][1];
    } else if (op == 'B') {
      x -= DIR_DELTA[d][0];
      y -= DIR_DELTA[d][1];
    } else if (op == 'L') {
      d = (d + 1) % 4;
    } else if (op == 'R') {
      d = (d + 3) % 4;
    }
  }
  return { { x, y }, d };
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);

  cin >> N >> X >> Y >> DC >> A;
  D = find(DIRS, DIRS + 4, DC) - DIRS;
  pair<pii, int> target = { { X, Y }, D };

  int change_i = -1; char change_op = 0;
  if (simulate() == target) change_i = 0;
  else {
    REP (i, N) {
      char old = A[i - 1];
      FOR (k, 4) if (OPS[k] != old) {
        A[i - 1] = OPS[k];
        if (simulate() == target) {
          change_i = i;
          change_op = OPS[k];
          break;
        }
      }
      A[i - 1] = old;
      if (change_i != -1) break;
    }
  }

  cout << change_i;
  if (change_i > 0) cout << " " << change_op;
  cout << endl;

  return 0;
}
