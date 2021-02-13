//distances.cpp created at 01/29/21 21:18:59

#include <bits/stdc++.h>

using namespace std;

const int MN = 101;

int N;
set<int> adj[MN];

int ans[MN], idx;

void dfs(const int u, const int par, const bool early) {
    if (early) {
        ans[idx++] = u;
    }

    for (const int v: adj[u]) {
        if (v == par) continue;
        dfs(v, u, !early);
    }

    if (!early) {
        ans[idx++] = u;
    }
}

void solve() {
    cin >> N;
    for (int i=0; i<N; ++i) {
        adj[i].clear();
    }

    for (int i=0; i<N-1; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        adj[u].insert(v);
        adj[v].insert(u);
    }

    idx = 0;
    dfs(0, -1, false);

    for (int i=0; i<N; ++i) {
        if (i) cout << ' ';
        cout << ans[i] + 1;
    }
    cout << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int T;
    cin >> T;

    for (int t=1; t<=T; ++t) {
        solve();
    }
}
