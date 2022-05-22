#include <bits/stdc++.h>

using namespace std;

using pii=pair<int,int>;

#define eb emplace_back

constexpr int MN = 1003;

int N, M, T;
vector<pii> adj[MN];

int par[MN], sz[MN];
int root(int u) {
    return u == par[u] ? u : par[u] = root(par[u]);
}
bool join(int u, int v) {
    int ru = root(u);
    int rv = root(v);
    if (ru == rv) return false;
    if (sz[ru] < sz[rv]) swap(ru, rv);

    par[rv] = par[v] = ru;
    sz[ru] += sz[rv];
    return true;
}

int dp[MN][MN]; // dreary, node

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> M >> T;
    --T;

    for (int i=0; i<N; ++i) {
        par[i] = i;
        sz[i] = 1;
    }

    for (int i=0; i<M; ++i) {
        int a, b, x;
        cin >> a >> b >> x;
        --a; --b;

        if (x == 0) {
            join(a, b);
        } else {
            adj[a].eb(b, x);
            adj[b].eb(a, x);
        }
    }

    for (int i=0; i<MN; ++i) {
        for (int j=0; j<MN; ++j) {
            dp[i][j] = 1e9;
        }
    }
    dp[0][root(0)] = 0;
    for (int d=1; d<=M; ++d) {
        for (int u=0; u<N; ++u) {
            for (const pii& p: adj[u]) {
                if (p.second > 0) {
                    dp[d][root(u)] = min(dp[d][root(u)], dp[d-1][root(p.first)] + (d - 1) * p.second);
                }
            }
        }
    }

    int ans = 1e9;
    for (int d=0; d<=M; ++d) {
        ans = min(ans, dp[d][root(T)]);
    }

    cout << (ans == 1e9 ? -1 : ans) << '\n';
}
