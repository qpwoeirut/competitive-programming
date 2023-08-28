//1146f.cpp created at 01/31/21 16:30:14

// had to read editorial 3 times, look at editorial code twice, and read somebody else's code as well

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MN = 200005;
const ll MOD = 998244353;

int N;
set<int> adj[MN];

ll dp[MN][3];
ll p2[MN];

void dfs(const int u) {
    dp[u][0] = dp[u][1] = dp[u][2] = 0;
    if (adj[u].empty()) {
        dp[u][2] = 1;
        return;
    }
    dp[u][0] = 1;
    for (const int v: adj[u]) {
        dfs(v);
        const ll incl = dp[v][1] + dp[v][2];
        const ll excl = dp[v][0] + dp[v][2];
        dp[u][2] = (dp[u][2] * (incl + excl) + dp[u][1] * incl) % MOD;
        dp[u][1] = (dp[u][1] * excl + dp[u][0] * incl) % MOD;
        dp[u][0] = (dp[u][0] * excl) % MOD;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;

    for (int i=1; i<N; ++i) {
        int v;
        cin >> v;
        --v;
        adj[v].insert(i);
    }

    p2[0] = 1;
    for (int i=1; i<N; ++i) {
        p2[i] = p2[i-1] << 1;
        if (p2[i] >= MOD) p2[i] -= MOD;
    }

    dfs(0);

    //for (int i=0; i<N; ++i) { cerr << dp[i] << ' ' << diff[i] << endl; }

    ll ans = (dp[0][0] + dp[0][2]) % MOD;
    if (ans < 0) ans += MOD;
    cout << ans << endl;
}

/*
6
1 1 2 3 3
*/
