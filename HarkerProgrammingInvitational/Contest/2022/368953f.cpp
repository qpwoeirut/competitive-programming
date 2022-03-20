#include <bits/stdc++.h>

using namespace std;

using ll=long long;
using pii=pair<const ll,ll>;

#define fi first
#define se second

const int MN = 102;
const ll MOD = 998244353;

int N, S;
set<pii> adj[MN];

ll binpow(const ll b, const ll p) {
    if (p == 0) return 1;
    if (p & 1) return (b * binpow(b, p - 1)) % MOD;
    return binpow((b * b) % MOD, p >> 1);
}

map<ll,ll> costs[MN];
void dfs(const int u, const int par) {
    costs[u][0] = 1;

    int sz = (int)(adj[u].size()) + (par == -1) - 1;
    if (sz < 2) return;

    for (const pii& p: adj[u]) {
        if (p.fi == par) continue;
        dfs(p.fi, u);
    }
    for (const pii& p1: adj[u]) {
        for (const pii& p2: adj[u]) {
            if (p1 == p2 || p1.fi == par || p2.fi == par) continue;

            const int a = p1.fi;
            const int b = p2.fi;

            for (const pii& pa: costs[a]) {
                for (const pii& pb: costs[b]) {
                    costs[u][pa.fi + pb.fi + p1.se + p2.se] += (pa.se * pb.se) % MOD;
                }
            }
        }
    }
    for (pii& p: costs[u]) p.se %= MOD;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> S;
    for (int i=0; i<N-1; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        --u; --v;
        adj[u].emplace(v, w);
        adj[v].emplace(u, w);
    }

    dfs(0, -1);
    ll numer = 0;
    for (const pii& p: costs[0]) {
        if (p.fi == 0) continue;
        numer += p.se;
    }
    numer %= MOD;
    numer = (numer * binpow(2, MOD - 2)) % MOD;
    ll denom = binpow(2, N);

    ll ans = (numer * binpow(denom, MOD - 2)) % MOD;

    cerr << numer << ' ' << denom << endl;
    cout << ans << '\n';
}
