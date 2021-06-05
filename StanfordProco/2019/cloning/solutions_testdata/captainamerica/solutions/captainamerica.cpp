#include <bits/stdc++.h>
#define FOR(i, n) for (int i = 0; i < (n); ++i)
#define ROF(i, n) for (int i = (n) - 1; i >= 0; --i)
#define REP(i, n) for (int i = 1; i <= (n); ++i)
#define REP3(i, s, n) for (int i = (s); i <= (n); ++i)
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int MAXQ = 500005;
int Q, T[MAXQ][3];
map<pii, set<int>> edge_tris;
set<pii> edges;

void add_edge(int u, int v) {
  if (u > v) swap(u, v);
  edges.insert(pii(u, v));
}

bool has_edge(int u, int v) {
  if (u > v) swap(u, v);
  return edges.count(pii(u, v));
}

void del_edge(int u, int v) {
  if (u > v) swap(u, v);
  edges.erase(pii(u, v));
}

void erase_edge_tri(int u, int v, int w) {
  auto it = edge_tris.find(pii(u, v));
  if (it == edge_tris.end()) return;
  it->second.erase(w);
  if (it->second.empty()) edge_tris.erase(it);
}

void add_triangle(int u, int v, int w) {
  T[w][0] = u; T[w][1] = v; T[w][2] = w;
  sort(T[w], T[w] + 3);
  edge_tris[pii(T[w][0], T[w][1])].insert(w);
  edge_tris[pii(T[w][0], T[w][2])].insert(w);
  edge_tris[pii(T[w][1], T[w][2])].insert(w);
}

int del_triangle(int u, int v) {
  if (u > v) swap(u, v);
  auto it = edge_tris.find(pii(u, v));
  if (it == edge_tris.end()) return 0;
  vector<int> ws(it->second.begin(), it->second.end());
  for (auto w : ws) {
    erase_edge_tri(T[w][0], T[w][1], w);
    erase_edge_tri(T[w][0], T[w][2], w);
    erase_edge_tri(T[w][1], T[w][2], w);
  }
  return ws.size();
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  cin >> Q;
  int triangles = 0;
  REP (w, Q) {
    int type, u, v;
    cin >> type >> u >> v;
    if (type == 0) { // append
      add_edge(u, w);
      if (u != v) {
        add_edge(v, w);
        if (has_edge(u, v)) {
          add_triangle(u, v, w);
          ++triangles;
        }
      }
    } else { // extend
      triangles -= del_triangle(u, v);
      del_edge(u, v);
      add_edge(u, w);
      add_edge(v, w);
    }
    cout << triangles << endl;
  }
  return 0;
}
