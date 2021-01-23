//chase.cpp created at 01/21/21 21:45:02

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MN = 100005;
const int MK = 102;

int N, K;
ll A[MN];
set<int> adj[MN];

ll nsum[MN];
ll dp[MN][MK][3];
// [node][k ][time since bread]

void preprocess(const int u, const int par) {
    nsum[u] = 0;
    for (const int v: adj[u]) {
        if (v == par) continue;
        nsum[u] += A[v];
        preprocess(v, u);
    }
}

void chmx(ll& a, const ll b) {
    if (a<b) a=b;
}

ll ans = 0;
void dfs(const int u, const int par) {
    for (int k=0; k<=K; ++k) {
        for (int i=0; i<3; ++i) {
            chmx(dp[u][k][i], par == -1 ? 0 : dp[par][k][max(0, i-1)]);
            chmx(ans, dp[u][k][i]);
        }
        if (k > 0) {
            chmx(dp[u][k][0],
                 nsum[u] + (par == -1 ? 0 : max({dp[par][k-1][2] + A[par], dp[par][k-1][0], dp[par][k-1][1]})));
            chmx(ans, dp[u][k][0]);
        }
    }
    for (const int v: adj[u]) {
        if (v == par) continue;
        dfs(v, u);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    
    cin >> N >> K;
    for (int i=0; i<N; ++i) {
        cin >> A[i];
    }
    for (int i=0; i<N-1; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        adj[a].insert(b);
        adj[b].insert(a);
    }

    for (int root=0; root<N; ++root) {
        for (int i=0; i<N; ++i) {
            for (int j=0; j<=K; ++j) {
                dp[i][j][0] = dp[i][j][1] = dp[i][j][2] = 0;
            }
        }
        preprocess(root, -1);
        dfs(root, -1);
        //for (int i=0; i<N; ++i) { cerr << nsum[i] << ' '; } cerr << endl; cerr << endl;
        //for (int i=0; i<N; ++i) { for (int j=1; j<=K; ++j) {
        //    for (int k=0; k<3; ++k) { cerr << dp[i][j][k] << ' '; } cerr << endl;
        //} cerr << endl; } cerr << "=========" << endl;
        if (N > 1000) break;
    }

    cout << ans << endl;
}
/*
12 2
2 3 3 8 1 5 6 7 8 3 5 4
2 1
2 7
3 4
4 7
7 6
5 6
6 8
6 9
7 10
10 11
10 12

7 2
1 2 4 8 16 32 64
1 3
2 3
3 4
4 5
5 6
5 7
*/
