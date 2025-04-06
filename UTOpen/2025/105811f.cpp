#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <iostream>

using namespace std;
using ll=long long;

const ll MOD = 1e9 + 7;

ll binpow(ll a, ll x, const ll mod) {
    ll ret = 1;
    for (; x > 0; x >>= 1) {
        if (x & 1) ret = (ret * a) % mod;
        a = (a * a) % mod;
    }
    return ret;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int N, M, K;
    cin >> N >> M >> K;
    int G[50][50][6];
    int degree[50];
    ll ideg[50];
    ll dp[8][50];

    for (int i=0; i<N; ++i) {
        degree[i] = ideg[i] = 0;
        for (int j=0; j<N; ++j) {
            for (int t=0; t<=5; ++t) {
                G[i][j][t] = 0;
            }
        }
    }
    for (int i=0; i<8; ++i) {
        for (int j=0; j<N; ++j) {
            dp[i][j] = 0;
        }
    }

    for (int i=0; i<M; ++i) {
        int u, v, t;
        cin >> u >> v >> t; --u; --v;
        ++G[u][v][t];
        ++G[v][u][t];
    }
    for (int i=0; i<N; ++i) {
        for (int t=1; t<=5; ++t) {
            G[N-1][i][t] = 0;
        }
    }
    for (int i=0; i<N; ++i) {
        for (int j=0; j<N; ++j) {
            for (int t=1; t<=5; ++t) {
                degree[i] += G[i][j][t];
            }
            ideg[i] = binpow(degree[i], MOD - 2, MOD);
        }
    }

    if (degree[0] == 0) {
        cout << "0\n";
        return 0;
    }

    dp[0][N-1] = 1;
    for (int k=1; k<=K; ++k) {
        dp[k & 7][N-1] = 1;
        for (int u=0; u<N-1; ++u) {
            ll tmp = 0;
            for (int v=0; v<N; ++v) {
                tmp += (dp[(k + 7) & 7][v] * G[u][v][1])
                     + (dp[(k + 6) & 7][v] * G[u][v][2])
                     + (dp[(k + 5) & 7][v] * G[u][v][3])
                     + (dp[(k + 4) & 7][v] * G[u][v][4])
                     + (dp[(k + 3) & 7][v] * G[u][v][5]);
            }
            dp[k & 7][u] = (tmp % MOD) * ideg[u] % MOD;
        }
    }

    cout << dp[K & 7][0] << '\n';
}
/*
3 4 10000
1 2 1
1 2 3
2 3 2
1 3 1
*/
