#include <bits/stdc++.h>
#define FOR(i, n) for (int i = 0; i < (n); ++i)
#define ROF(i, n) for (int i = (n) - 1; i >= 0; --i)
#define REP(i, n) for (int i = 1; i <= (n); ++i)
#define REP3(i, s, n) for (int i = (s); i <= (n); ++i)
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int NODES = 26 * 26, MAXN = 1000;
int N, bis, tris;
vector<int> g[NODES];
bool bi[NODES], tri[26][26][26];
char diagonal[MAXN * 2 - 1];

string repr(int u) {
  return string() + (char) ((u / 26) + 'a') + (char) ((u % 26) + 'a');
}

int color[NODES], dfs_path[NODES];
int cycle[NODES], cycle_len;
int toposort[NODES], toposort_index;
bool dfs_cycle(int u, int depth = 0) {
  if (color[u] == 1) {
    int st = depth - 1;
    while (dfs_path[st] != u) --st;
    cycle_len = depth - st;
    copy(dfs_path + st, dfs_path + depth, cycle);
    return true;
  }
  if (color[u] == 2) return false;
  color[u] = 1;
  dfs_path[depth] = u;
  if (bi[u]) {
    for (auto v : g[u]) if (dfs_cycle(v, depth + 1)) return true;
  }
  color[u] = 2;
  toposort[toposort_index++] = u;
  return false;
}

int max_len[NODES], max_u[NODES];

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  cin >> N >> bis >> tris;

  memset(bi, true, sizeof bi);
  memset(tri, true, sizeof tri);
  FOR (i, bis) {
    char a, b;
    cin >> a >> b;
    bi[(a - 'a') * 26 + (b - 'a')] = false;
  }
  FOR (i, tris) {
    char a, b, c;
    cin >> a >> b >> c;
    tri[a - 'a'][b - 'a'][c - 'a'] = false;
  }
  FOR (i, 26) FOR (j, 26) FOR (k, 26)
    if (tri[i][j][k]) {
      g[i * 26 + j].emplace_back(j * 26 + k);
    }

  bool ok = false;
  FOR (i, NODES) if (dfs_cycle(i)) break;

  if (cycle_len) {
    ok = true;
    FOR (i, 2 * N - 1) diagonal[i] = (char) ((cycle[i % cycle_len] / 26) + 'a');
  } else {
    int best_u = -1, best_len = 0;
    fill(max_u, max_u + NODES, -1);
    FOR (i, NODES) {
      int u = toposort[i];
      if (!bi[u]) max_len[u] = 0;
      else {
        max_len[u] = 1;
        for (auto v : g[u]) {
          if (bi[v] && max_len[u] < max_len[v] + 1) {
            max_len[u] = max_len[v] + 1;
            max_u[u] = v;
          }
        }
      }

      if (best_len < max_len[u]) {
        best_len = max_len[u];
        best_u = u;
      }
    }

    if (best_len >= 2 * N - 2) {
      ok = true;
      diagonal[0] = (char) ((best_u / 26) + 'a');
      FOR (i, 2 * N - 2) {
        diagonal[i + 1] = (char) ((best_u % 26) + 'a');
        best_u = max_u[best_u];
      }
    }
  }

  cout << ok << endl;
  if (ok) {
    FOR (i, N) {
      FOR (j, N) cout << diagonal[i + j];
      cout << endl;
    }
  }

  return 0;
}
