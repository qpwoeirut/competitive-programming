//usaco_gold15_palpaths.cpp created at 12/19/20 17:51:38

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MN = 505;
const ll MOD = 1e9 + 7;

int N;
char G[MN][MN];

ll dp[2][MN][MN];

int main() {
    freopen("palpath.in", "r", stdin);
    freopen("palpath.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=1; i<=N; ++i) {
        for (int j=1; j<=N; ++j) {
            cin >> G[i][j];
        }
    }

    dp[0][1][N] = 1;
    for (int i=1; i<N; ++i) {
        for (int r1=1; r1<=i+1; ++r1) {
            int c1 = i - r1 + 2;
            for (int r2=N; r2>=N-i; --r2) {
                const int c2 = N + N - r2 - i;

                dp[i&1][r1][r2] = 0;
                if (G[r1][c1] == G[r2][c2]) {
                    dp[i&1][r1][r2] = (dp[!(i&1)][r1-1][r2+1] + dp[!(i&1)][r1-1][r2] + dp[!(i&1)][r1][r2+1] + dp[!(i&1)][r1][r2]) % MOD;
                }
            }
        }
    }

    ll ans = 0;
    for (int i=1; i<=N; ++i) {
        ans += dp[!(N&1)][i][i];
        if (ans >= MOD) ans -= MOD;
    }
                        
    cout << ans << endl;
}

