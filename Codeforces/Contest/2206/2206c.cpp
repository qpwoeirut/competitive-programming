#include <bits/stdc++.h>

using namespace std;

const int MN = 200005;
const int MAX = 10'000'000;

int N, M;
map<int,int> adj[MN];
int S[MN];

int weight[MN];

int s_i;
bitset<MN> vis;
bool dfs(int u) {
    if (vis[u]) return false;
    vis[u] = true;
    if (s_i == N) return true;

    auto it = adj[u].find(S[s_i]);
    while (it != adj[u].end()) {
        weight[it->second] = MAX - s_i;
        ++s_i;
        bool ok = dfs(it->first);
        if (!ok) return false;

        if (s_i == N) break;
        it = adj[u].find(S[s_i]);
    }

    for (const auto& [v, i]: adj[u]) {
        if (!vis[v]) return false;
    }
    return true;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> M;

    for (int i=0; i<M; ++i) {
        int u, v;
        cin >> u >> v; --u; --v;
        adj[u][v] = i;
        adj[v][u] = i;
    }

    for (int i=0; i<N; ++i) {
        cin >> S[i]; --S[i];
    }

    fill(weight, weight+M, 1);
    vis.reset();
    s_i = 1;
    bool ok = dfs(0);
    if (ok) {
        for (int i=0; i<M; ++i) {
            if (i) cout << ' ';
            cout << weight[i];
        }
        cout << '\n';
    } else {
        cout << "impossible\n";
    }
}
