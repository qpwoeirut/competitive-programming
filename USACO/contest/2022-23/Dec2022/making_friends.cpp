#include <bits/stdc++.h>

using namespace std;

constexpr int MN = 200005;

int N, M;
set<int> adj[MN];

int main() {
    cin.tie()->sync_with_stdio(0);

    cin >> N >> M;
    for (int i=0; i<M; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;

        adj[u].insert(v);
        adj[v].insert(u);
    }

    int ans = 0;
    for (int i=0; i<N; ++i) {
        for (const int u: adj[i]) {
            adj[u].erase(i);
        }

        for (const int u: adj[i]) {
            for (const int v: adj[i]) {
                if (u != v && adj[u].insert(v).second) ++ans;
            }
        }

        adj[i].clear();
    }

    assert(ans % 2 == 0);
    ans >>= 1;
    cout << ans << '\n';
}
