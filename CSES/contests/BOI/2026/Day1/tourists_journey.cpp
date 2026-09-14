#include <bits/stdc++.h>

using namespace std;

using pii = pair<int, int>;

const int MOD = 1e9 + 7;

const int MN = 200015;
const int MK = 10004;

int N;
pii edge[MN];
set<int> adj[MN];

int dfs(int u, int finish, int par, int k) {
    if (k == 0) return u == finish;

    int ret = 0;
    for (int v: adj[u]) {
        if (v != par) ret += dfs(v, finish, u, k - 1);
    }
    return ret;
}

int dp[2][MN][2];
int dp_n[MN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int M, K;
    cin >> N >> M >> K;

    for (int j=0; j<M; ++j) {
        int u, v;
        cin >> u >> v; --u; --v;
        edge[j] = pii(u, v);
        adj[u].insert(v);
        adj[v].insert(u);
    }

    if (M <= N) {
        bool changed = false;
        do {
            changed = false;
            for (int u=1; u<N-1; ++u) {
                if (adj[u].size() == 1) {
                    adj[*adj[u].begin()].erase(u);
                    adj[u].clear();
                    changed = true;
                }
            }
        } while (changed);

        int start = 0;
        int finish = N - 1;
        while (adj[start].size() == 1 && K > 1) {
            int new_start = *adj[start].begin();
            if (new_start == finish || adj[new_start].size() > 2) break;
            adj[new_start].erase(start);
            adj[start].clear();
            start = new_start;
            --K;
        }
        while (adj[finish].size() == 1 && K > 1) {
            int new_finish = *adj[finish].begin();
            if (new_finish == start || adj[new_finish].size() > 2) break;
            adj[new_finish].erase(finish);
            adj[finish].clear();
            finish = new_finish;
            --K;
        }
        int ans = dfs(start, finish, -1, K);
        cout << ans << '\n';
        return 0;
    }

    for (int j=0; j<M; ++j) {
        dp[0][j][0] = edge[j].first == 0;
        dp[0][j][1] = edge[j].second == 0;
    }
    for (int i=0; i<K; ++i) {
        int ii = i & 1;

        for (int u=0; u<N; ++u) dp_n[u] = 0;
        for (int j=0; j<M; ++j) {
            dp_n[edge[j].second] = (dp_n[edge[j].second] + dp[ii][j][0]) % MOD;
            dp_n[edge[j].first] = (dp_n[edge[j].first] + dp[ii][j][1]) % MOD;
        }

        for (int j=0; j<M; ++j) dp[ii^1][j][0] = dp[ii^1][j][1] = 0;
        for (int j=0; j<M; ++j) {
            dp[ii^1][j][0] = (dp[ii^1][j][0] + dp_n[edge[j].first] - dp[ii][j][1]) % MOD;
            dp[ii^1][j][1] = (dp[ii^1][j][1] + dp_n[edge[j].second] - dp[ii][j][0]) % MOD;
        }
    }

    int ans = 0;
    for (int j=0; j<M; ++j) {
        int k = K & 1;
        if (edge[j].second == N - 1) ans = (ans + dp[k^1][j][0]) % MOD;
        if (edge[j].first == N - 1) ans = (ans + dp[k^1][j][1]) % MOD;
    }

    cout << (ans + MOD) % MOD << '\n';
}

/*
9 9 1000009
1 2
2 3
3 4
4 5
5 1
5 6
1 7
7 8
3 9
*/
