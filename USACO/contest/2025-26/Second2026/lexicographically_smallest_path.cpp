#include <bits/stdc++.h>

using namespace std;

const int MN = 200005;

int N, M;
vector<pair<int, char>> adj[MN];
int ans[MN];

void solve() {
    fill(ans, ans+N, -1);

    set<int> active, nxt;
    active.insert(0);

    char cur = 'z';
    for (int d=0; d<N; ++d) {
        for (int u: active) {
            ans[u] = d;
        }

        for (int u: active) {
            for (const auto& [v, val]: adj[u]) {
                cur = min(cur, val);
            }
        }

        for (int u: active) {
            for (const auto& [v, val]: adj[u]) {
                if (val == cur && ans[v] == -1) nxt.insert(v);
            }
        }
        
        swap(active, nxt);
        nxt.clear();
    }

    for (int i=0; i<N; ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int T;
    cin >> T;

    while (T --> 0) {
        cin >> N >> M;
        for (int i=0; i<N; ++i) {
            adj[i].clear();
        }
        for (int i=0; i<M; ++i) {
            int u, v;
            char c;
            cin >> u >> v >> c; --u; --v;

            if (adj[u].size() > 0 && adj[u].back().second > c) adj[u].clear();
            if (adj[u].size() == 0 || adj[u].back().second == c) adj[u].emplace_back(v, c);

            if (adj[v].size() > 0 && adj[v].back().second > c) adj[v].clear();
            if (adj[v].size() == 0 || adj[v].back().second == c) adj[v].emplace_back(u, c);

        }
        solve();
    }
}
