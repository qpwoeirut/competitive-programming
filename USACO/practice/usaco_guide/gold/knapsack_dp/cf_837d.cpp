//cf_837d.cpp created at 12/19/20 17:16:13

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MN = 205;
const int MF = 50 * MN;

int N, K;
int five[MN], two[MN];

int dp[2][MN][MF];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    
    cin >> N >> K;
    for (int i=0; i<N; ++i) {
        ll x;
        cin >> x;
        while ((x & 1) == 0) {
            ++two[i];
            x >>= 1;
        }
        while ((x % 5) == 0) {
            ++five[i];
            x /= 5;
        }
    }

    for (int j=0; j<=K; ++j) {
        for (int k=0; k<MF; ++k) {
            dp[0][j][k] = dp[1][j][k] = -1001001001;
        }
    }

    dp[0][0][0] = dp[1][0][0] = 0;
    int ans = 0;
    for (int i=1; i<=N; ++i) {
        for (int j=1; j<=K && j<=i; ++j) {
            for (int k=0; k<MF; ++k) {
                dp[i&1][j][k] = dp[!(i&1)][j][k];
                if (k >= five[i-1]) {
                    dp[i&1][j][k] = max(dp[i&1][j][k], dp[!(i&1)][j-1][k - five[i-1]] + two[i-1]);
                }

                if (j == K) {
                    ans = max(ans, min(k, dp[i&1][j][k]));
                }
            }
        }
    }

    cout << ans << endl;
}

