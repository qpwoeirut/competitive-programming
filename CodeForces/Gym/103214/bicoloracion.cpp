//bicoloracion.cpp created at 08/06/21 12:20:07

#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pll = pair<ll,ll>;

#define fi first
#define se second

const int MN = 100005;
const ll INF = 1e18;

int N, M;
set<pll> adj[MN];

int color[MN];
bool dfs(const int u, const int v, const int c, const ll D) {
    if (color[u] != -1 && color[u] != c) return false;
    if (color[u] == c) return true;

    color[u] = c;
    for (const pll& p: adj[u]) {
        if (p.se < D) if (!dfs(p.fi, u, c^1, D)) return false;
    }
    return true;
}

bool check(const ll D) {
    for (int i=0; i<N; ++i) {
        ll w1 = INF;
        for (const pll& p: adj[i]) {
            if (w1 + p.se < D) return false;
            w1 = min(w1, p.se);
        }
    }

    fill(color, color+N, -1);
    for (int i=0; i<N; ++i) {
        if (color[i] == -1) if (!dfs(i, -1, 0, D)) return false;
    }
    return true;
}

string solve() {
    ll lo = 0, hi = INF;
    while (lo < hi) {
        ll mid = (lo + hi + 1) >> 1;
        if (check(mid)) {
            lo = mid;
        } else {
            hi = mid - 1;
        }
    }

    if (hi > INF / 100) return "INF";
    return to_string(lo);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int T;
    cin >> T;
    while (T--) {
        cin >> N >> M;
        for (int i=0; i<N; ++i) adj[i].clear();
        for (int i=0; i<M; ++i) {
            int u, v, w;
            cin >> u >> v >> w;
            adj[u].emplace(v, w);
            adj[v].emplace(u, w);
        }
        cout << solve() << '\n';
    }
}
