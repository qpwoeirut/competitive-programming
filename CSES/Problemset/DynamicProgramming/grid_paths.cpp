//grid_paths.cpp created at 12/17/20 18:26:56

#include <bits/stdc++.h>

using namespace std;

const int MN = 1005;
const int MOD = 1e9 + 7;

int N;
bool G[MN][MN];

int dp[MN][MN];

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    for (int i=1; i<=N; ++i) {
        for (int j=1; j<=N; ++j) {
            char c;
            cin >> c;
            G[i][j] = c == '.';
        }
    }

    dp[1][1] = G[1][1];
    for (int i=1; i<=N; ++i) {
        for (int j=1; j<=N; ++j) {
            if ((i != 1 || j != 1) && G[i][j]) {
                dp[i][j] = dp[i-1][j] + dp[i][j-1];
                if (dp[i][j] >= MOD) dp[i][j] -= MOD;
            }
        }
    }

    cout << dp[N][N] << endl;
}

