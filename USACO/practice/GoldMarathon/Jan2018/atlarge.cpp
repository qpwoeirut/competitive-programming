#include <bits/stdc++.h>

using namespace std;

const int MN = 100005;

int N, K;
set<int> adj[MN];

int ldist[MN];

void dfs(const int node, const int par) {
    if (adj[node].size() == 1) {
        ldist[node] = 0;
        return;
    }

    ldist[node] = N;
    for (auto it=adj[node].begin(); it!=adj[node].end(); ++it) {
        if (*it == par) continue;
        dfs(*it, node);
        ldist[node] = min(ldist[node], ldist[*it] + 1);
    }
}

int ans = 0;
void dfs2(const int node, const int par, const int dist) {
    if (dist >= ldist[node]) {
        ++ans;
        return;
    }
    for (auto it=adj[node].begin(); it!=adj[node].end(); ++it) {
        if (*it == par) continue;
        dfs2(*it, node, dist + 1);
    }
}

int main() {
    freopen("atlarge.in", "r", stdin);
    freopen("atlarge.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> K;
    --K;
    for (int i=0; i<N-1; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;

        adj[u].insert(v);
        adj[v].insert(u);
    }

    dfs(K, -1);
    dfs2(K, -1, 0);

    cout << ans << endl;
}
