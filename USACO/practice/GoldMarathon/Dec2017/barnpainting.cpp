#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MN = 100005;
const ll MOD = 1e9 + 7;

int N, K;
int A[MN];
set<int> adj[MN];

ll dp[MN][3];

inline int add(const int a, const int b) {
    return (a+b >= 3) ? a+b-3 : a+b;
}

ll dfs(const int node, const int par, const int color) {
    if (dp[node][color] != -1) {
        return dp[node][color];
    }
    //cerr << node << ' ' << color << endl;

    dp[node][color] = 1;
    for (auto it=adj[node].begin(); it!=adj[node].end(); ++it) {
        if (*it == par) continue;
        ll c1 = dfs(*it, node, add(color, 1));
        ll c2 = dfs(*it, node, add(color, 2));
        dp[node][color] = (dp[node][color] * (c1 + c2)) % MOD;
    }

    return dp[node][color];
}

int main() {
    freopen("barnpainting.in", "r", stdin);
    freopen("barnpainting.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> K;
    for (int i=0; i<N-1; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        adj[u].insert(v);
        adj[v].insert(u);
    }
    for (int i=0; i<N; ++i) {
        dp[i][0] = dp[i][1] = dp[i][2] = -1;
    }

    fill(A, A+N, -1);
    for (int i=0; i<K; ++i) {
        int idx, c;
        cin >> idx >> c;
        --idx; --c;
        A[idx] = c;
        dp[idx][add(c, 1)] = 0;
        dp[idx][add(c, 2)] = 0;
    }

    ll ans = dfs(0, -1, 0) + dfs(0, -1, 1) + dfs(0, -1, 2);
    cout << ans % MOD << endl;
}
