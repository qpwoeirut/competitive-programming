#include <bits/stdc++.h>

using namespace std;
using pii=pair<int,int>;
using ll=long long;

#define fi first
#define se second

const int MN = 10004;
const int MOD = 1e9 + 7;

int N, M;
ll A[MN];
pii edge[MN * 2];
vector<int> adj[MN];

ll inv(ll x) {
    ll ret = 1;
    for (ll p = MOD - 2; p > 0; p >>= 1) {
        if (p & 1) ret = (ret * x) % MOD;
        x = (x * x) % MOD;
    }
    return ret;
}

ll ans[MN];

bitset<MN * 2> used;
void dfs(int u, ll p) {
    ans[u] = (ans[u] + (p * A[u])) % MOD;
    p = (p * (1 - A[u])) % MOD;

    vector<pii> available;
    for (int i=0; i<M; ++i) {
        if (used[i]) continue;
        if (edge[i].fi == u) available.emplace_back(i, edge[i].se);
        if (edge[i].se == u) available.emplace_back(i, edge[i].fi);
    }

    if (available.empty()) {
        ans[u] = (ans[u] + p) % MOD;
    } else {
        for (const pii& bridge: available) {
            used[bridge.fi] = true;
            dfs(bridge.se, (p * inv(available.size())) % MOD);
            used[bridge.fi] = false;
        }
    }
}

void brute() {
    fill(ans, ans+N, 0);
    used.reset();
    dfs(0, 1);
    for (int i=0; i<N; ++i) {
        ans[i] = ((ans[i] % MOD) + MOD) % MOD;
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
        for (int i=0; i<N; ++i) adj[i].clear();

        for (int i=0; i<N; ++i) {
            cin >> A[i];
        }
        for (int i=0; i<M; ++i) {
            cin >> edge[i].fi >> edge[i].se; --edge[i].fi; --edge[i].se;
            adj[edge[i].fi].push_back(edge[i].se);
            adj[edge[i].se].push_back(edge[i].fi);
        }

        brute();
    }
}
