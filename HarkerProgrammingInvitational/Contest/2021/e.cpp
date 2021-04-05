#include <bits/stdc++.h>

using namespace std;

const int MN = 100005;
const int MOD = 1e9 + 7;

typedef long long ll;

int N, M;
set<int> adj[MN];
set<int> ok[MN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> M;

    for (int i=0; i<N-1; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        adj[u].insert(v);
        adj[v].insert(u);
    }

    for (int i=0; i<N; ++i) {
        for (int j=1; j<=M; ++j) {
            ok[i].insert(j);
        }
    }

    for (int i=0; i<N; ++i) {
        int K;
        cin >> K;
        for (int j=0; j<K; ++j) {
            int x;
            cin >> x;
            for (const int v: adj[i]) {
                ok[v].erase(x);
            }
        }
    }

    ll ans = 1;
    for (int i=0; i<N; ++i) {
        ll m = ok[i].size();
        ans = (ans * m) % MOD;
    }
    cout << ans << '\n';
}
